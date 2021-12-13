//
//  global.hpp
//  New_try
//
//  Created by Yipei Zhang on 12/10/21.
//
#pragma once
#include "stock.hpp"

using namespace std;
class global_constant
{
public:
    map <string, stock > global_stock; //global variable
    int N_days; //global variable
    vector<vector<string>> stock_names;
    int get_N(){return N_days;};
    map<string, stock> MissSymbols;
    map<string, stock> MeetSymbols;
    map<string, stock> BeatSymbols;
    int group_size = 80;
    
    map<string,stock> check_size(map<string, stock> Symbol_list)
    {
        map<string, stock> one_group = Symbol_list;
        for(map<string, stock>::iterator itr = one_group.begin(); itr != one_group.end(); itr++)
        {
            if ((itr->second.get_price()).size() < (190))
            {
                int price_size = (int)(itr->second.get_price()).size();
                one_group.erase(itr);
                cout<< itr->first <<" does not have enough historical prices, only has " << price_size << endl;
            }
        }
        return one_group;
    }
};

