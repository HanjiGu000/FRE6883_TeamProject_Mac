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
#include "read_earning.hpp"


using namespace std;
typedef vector<double> Vector;
typedef vector<Vector> Matrix;


void input_N(global_constant& g)
{


    int N_;
    cout << "Please input N" << endl;
    cin >> N_;
    while ((N_ < 30) || ((N_ > 60)))
    {
        cout << "N should be greater than 30 and less than 60" << endl;
        cout << "Please continue to input N" << endl;
        cin >> N_;
    }
    g.N_days = N_;
}


int main(void) {
    char selection = NULL;
    bool runA = false;
    bool runB = false;
    global_constant g;
    //bootstrap boot;
    while(true)
    {
        cout << endl;
        cout << "Menu" << endl;
        cout << "======" << endl;
        cout << "A - Retrive Historical Price Data for All Stocks" << endl;
        cout << "B - Retrieve Benchmark Data and Calculate AAR and CAAR" << endl;
        cout << "C - Show AAR, AAR-SD, CAAR and CAAR-STD For Each Group" << endl;
        cout << "D - Show Graph with AAR, AAR-SD, CAAR and CAAR-STD" << endl;
        cout << "E - Pull Informations for One Stock" << endl;
        cout << "F - Exit" << endl;
   
        
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
                
                
                thread download1(ParseIntoMap, ref(MissSymbols), "miss_stocks.txt", g.N_days);
                thread download2(ParseIntoMap, ref(MeetSymbols), "meet_stocks.txt", g.N_days);
                thread download3(ParseIntoMap, ref(BeatSymbols), "beat_stocks.txt", g.N_days);
                download1.join();
                download2.join();
                download3.join();

                for (map<string, stock>::iterator itr = MissSymbols.begin(); itr != MissSymbols.end(); itr++) {
                    g.global_stock[itr->first] = itr->second;
                }
                for (map<string, stock>::iterator itr = MeetSymbols.begin(); itr != MeetSymbols.end(); itr++) {
                    g.global_stock[itr->first] = itr->second;
                }
                for (map<string, stock>::iterator itr = BeatSymbols.begin(); itr != BeatSymbols.end(); itr++) {
                    g.global_stock[itr->first] = itr->second;
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
                string benchmark = "IWB";
                int Nsamples;
                int group_size;
                //cout << "Enter Ticker for Benchmark Stock:" << endl;
                //cin >> benchmark;
                cout << "Enter Sample Size:" << endl;
                cin >> Nsamples;
                cout << "Enter size for each group:" << endl;
                cin >> group_size;
    
                stock stock_ = stock(benchmark);
                
                download(stock_, "2020-01-01", "2021-11-30");
                stock_.set_N(700);
                g.global_stock[benchmark] = stock_;
                
                for (map<string, stock>::iterator itr = g.global_stock.begin(); itr != g.global_stock.end(); itr++) {
                    itr->second.cal_return();
                }

                for (map<string, stock>::iterator itr = g.global_stock.begin(); itr != g.global_stock.end(); itr++) {
                    itr->second.cal_ARIT(g.global_stock[benchmark]);
                }
                /*
                boot.Set_N(g);
                boot.Set_N_samples(Nsamples);
                boot.set_group_size(group_size);
                boot.Repeat(g);
                boot.cal_result_matrix();
                */
                cout << "Calculation finished" << endl;
                runB = true;
                break;
                
                
                
            }
                
            case 'C':{
                /*
                if (!runA) {
                    cout << "Please run step A first" << endl;
                    break;
                }
                if (!runB) {
                    cout << "Please run step B first" << endl;
                    break;
                }
                */
                
            }
                
            case 'F': {
                exit(10);
            }
            
        }
    

    }
    
    
}
