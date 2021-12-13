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
    
};

