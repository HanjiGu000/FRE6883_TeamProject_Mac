//
//  shuffle.hpp
//  New_try
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
// to output a list of random stock names
vector<string> random(string key, map<string, stock> &clean_stock, int group_size){
        vector<string> output_symbols;
        vector<string> keys(3);
        map<string, stock> new_gather;
        vector<string> stock_name;
        
        keys[0] = "miss";
        keys[1] = "beat";
        keys[2] = "meet";
        if (key == "miss"){
            new_gather = clean_stock;
            for(map<string,stock>::iterator itr=new_gather.begin();itr!=new_gather.end();itr++) stock_name.push_back(itr->first);
        }
        else if (key == "meet"){
            new_gather = clean_stock;
            for(map<string,stock>::iterator itr=new_gather.begin();itr!=new_gather.end();itr++) stock_name.push_back(itr->first);
        }
        else if (key == "beat"){
            new_gather = clean_stock;
            for(map<string,stock>::iterator itr=new_gather.begin();itr!=new_gather.end();itr++) stock_name.push_back(itr->first);
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
            for (int j = 0; j < group_size; j++)
            {
                output_symbols.push_back(stock_name[temp[j]]);
            }
        return output_symbols;
    }
    

