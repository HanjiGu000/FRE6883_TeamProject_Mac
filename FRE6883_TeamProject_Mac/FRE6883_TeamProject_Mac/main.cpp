//
//  main.cpp
//  New_try
//
//  Created by Yipei Zhang on 12/10/21.
//
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <thread>
#include <iomanip>
#include "curl/curl.h"
#include <fstream>
#include <istream>
#include<map>

#include "global.hpp"
#include "stock.hpp"
#include "Libcurl.hpp"
//#include "Libcurl_new.hpp"
#include "read_earning.hpp"
#include "bootstrapping.hpp"
//#include "shuffle_stock.hpp"
using namespace std;
typedef vector<double> Vector;
typedef vector<Vector> Matrix;

void input_N(global_constant& g)
{
    int N_;
    cout << "Please input N" << endl;
    cin >> N_;
    while (N_ < 60)
    {
        cout << "N should be greater than 60" << endl;
        cout << "Please continue to input N" << endl;
        cin >> N_;
        g.N_days = N_;
    }
    g.N_days = N_;
}


int main(void) {
    char selection = NULL;
    bool runA = false;
    bool runB = false;
    global_constant g;
    g.stock_names.resize(3);
    
    while(true)
    {
        cout << endl;
        cout << "Menu" << endl;
        cout << "======" << endl;
        cout << "A - Retrive Historical Price Data for All Stocks" << endl;
        cout << "B - Bootstrapping, show AAR, AAR-SD, CAAR and CAAR-STD for each group" << endl;
        cout << "C - Gnuplot Option to show CAAR for all 3 groups" << endl;
        cout << "D - Pull Informations for One Stock" << endl;
        cout << "E - Exit" << endl;
        cin >> selection;
        
        switch (selection) {
            case 'A':
            {
                test mytest;
                mytest.run();
                
                input_N(g);
                map<string, stock> MissSymbols;
                map<string, stock> MeetSymbols;
                map<string, stock> BeatSymbols;
                
                thread download1(ParseIntoMap,ref(MissSymbols),"miss_stocks.txt",g.get_N());
                thread download2(ParseIntoMap,ref(MeetSymbols),"meet_stocks.txt",g.get_N());
                thread download3(ParseIntoMap,ref(BeatSymbols),"beat_stocks.txt",g.get_N());
                download1.join();
                download2.join();
                download3.join();
                MissSymbols.erase("");
                MeetSymbols.erase("");
                BeatSymbols.erase("");
                
                g.MissSymbols =MissSymbols;
                g.MeetSymbols =MeetSymbols;
                g.BeatSymbols =BeatSymbols;
                
                for (map<string, stock>::iterator itr = MissSymbols.begin(); itr != MissSymbols.end(); itr++) {
                    g.global_stock[itr->first] = itr->second;
                    g.stock_names[0].push_back(itr->first);
                    
                }
                for (map<string, stock>::iterator itr = MeetSymbols.begin(); itr != MeetSymbols.end(); itr++) {
                    g.global_stock[itr->first] = itr->second;
                    g.stock_names[1].push_back(itr->first);
                }
                for (map<string, stock>::iterator itr = BeatSymbols.begin(); itr != BeatSymbols.end(); itr++) {
                    g.global_stock[itr->first] = itr->second;
                    g.stock_names[2].push_back(itr->first);
                }
                g.stock_names[0].erase(g.stock_names[0].begin());
                g.stock_names[1].erase(g.stock_names[1].begin());
                g.stock_names[2].erase(g.stock_names[2].begin());
                
                string benchmark = "IWB";
                stock IWB = stock(benchmark);
                download(IWB, "2020-01-01", "2021-11-30");
                IWB.set_N(700);
                g.global_stock[benchmark] = IWB;
                
                for (map<string, stock>::iterator itr = g.global_stock.begin(); itr != g.global_stock.end(); itr++) {
                    itr->second.cal_return();
                    itr->second.cal_ARIT(g.global_stock[benchmark]);
                }
                cout << "Retrive data finished" << endl;
                runA = true;
                break;
            }
                
            case 'B':
            {
                if (!runA){
                    cout << "Please run step A first" << endl;
                    break;
                }
                vector<vector<double>> miss_together;
                vector<vector<double>> meet_together;
                vector<vector<double>> beat_together;
                //miss_together = output_one_sample(g, "miss");
                //meet_together = output_one_sample(g, "meet");
                //beat_together = output_one_sample(g, "beat");
                
                thread bootstrap1(output_one_sample,ref(miss_together),ref(g),"miss");
                thread bootstrap2(output_one_sample,ref(meet_together),ref(g),"meet");
                thread bootstrap3(output_one_sample,ref(beat_together),ref(g),"beat");
                bootstrap1.join();
                bootstrap2.join();
                bootstrap3.join();
                
                cout << "Calculation finished" << endl;
                runB = true;
                break;
            }
                
            case 'C':
            {
                
            }
                
            case 'D':
            {
                if (!runA) {
                    cout << "Please run step A first" << endl;
                    break;
                }
                string stockinput;
                bool pass = false;
                cout << " Input Stock Name(Upper Case): " << endl;
                cin >> stockinput;
                map<string,stock>::iterator it;
                it = g.global_stock.find(stockinput);
                if (it != g.global_stock.end()) pass = true;
                    
                if (pass == false){
                    cout << "Invalid Stock Name." << endl;
                    cout << "Back to main menu." << endl;
                    break;
                }
                stock info = g.global_stock[stockinput];
                map<string, double> input_price = info.get_price();
                map<string, double> stockinput_return = info.get_return();

                cout << "announce date: " << info.get_annouce_date() << endl;
                cout << "estimated earning: " << info.get_estimated() << endl;
                cout << "reported earning: " << info.get_reported() << endl;
                cout << "surprise: " << info.get_surprise() << endl;
                cout << "surprise %: " << info.get_surprise_percentage() << endl;
                cout << "======" << endl;
                cout << "Date" << "          " << "price" << "   " << "cumulative_return" << endl;
                double cumulative_return = 0;
                for (map<string, double>::iterator i = stockinput_return.begin(); i != stockinput_return.end(); i++) {
                    cumulative_return += i->second;
                    cout << i->first << "~~~" << input_price[i->first] << "  " << cumulative_return << endl;
                }
                break;
            }
                
            case 'E':
            {
                exit(10);
            }
                
        }
    

    }
    
}
