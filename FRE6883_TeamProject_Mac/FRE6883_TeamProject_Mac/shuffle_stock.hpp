//
//  shuffle_stock.hpp
//  FRE6883_TeamProject_Mac
//
//  Created by Yipei Zhang on 12/12/21.
//
#include<iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include<vector>
#include<string>
#include<map>
#include<time.h>
#include"stock.hpp"
#include <algorithm>
#include <random>
#include "global.hpp"

using namespace std;
vector<string> random(string key, global_constant g, int group_size){
        vector<string> output_symbols;
        vector<string> keys(3);
        map<string, stock> new_gather;
        vector<string> stock_name;
        
        keys[0] = "miss";
        keys[1] = "beat";
        keys[2] = "meet";
        if (key == "miss"){
            new_gather = g.MissSymbols;
            stock_name = g.stock_names[0];
        }
        else if (key == "meet"){
            new_gather = g.MeetSymbols;
            stock_name = g.stock_names[1];
        }
        else if (key == "beat"){
            new_gather = g.BeatSymbols;
            stock_name = g.stock_names[2];
        }
        
        for(map<string, stock>::iterator itr = new_gather.begin(); itr != new_gather.end(); itr ++){
            int price_size;
            string ticker;
            price_size = (int)(itr->second.get_price()).size();
            ticker = itr->first;
            if (ticker == "") continue;
            if (price_size < (2*g.get_N()+1))
            {
                //for(int)
                
                
                /*
                for (int i = 0; i < stock_name.size(); i++)
                {
                    for(int j = (int)stock_name[i].size(); j != 0 ; j--)
                    {
                        stock_name[i].erase(stock_name[i].end()-j);
                        cout << ticker << " does not have 2N+1 historical price"<< endl;
                    }
                }
                 */
            }
        }
                int size = (int)stock_name.size();
                vector<int> temp;
                for (int k = 0; k < size; k++)
                {
                    temp.push_back(k);
                }
                random_device rng;
                mt19937 urng(rng());
                shuffle(temp.begin(), temp.end(), urng);
                for(int j = 0; j< temp.size(); j++)
                {
                    
                }
                for (int j = 0; j < group_size; j++)
                {
                    output_symbols.push_back(stock_name[temp[j]]);
                }
            
        
        return output_symbols;
    }
    

