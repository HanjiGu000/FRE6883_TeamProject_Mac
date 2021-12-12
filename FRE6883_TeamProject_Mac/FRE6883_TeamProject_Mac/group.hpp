//
//  group.hpp
//  script
//
//  Created by Yipei Zhang on 12/10/21.
//

#pragma once
#include<map>
#include<string>
#include<vector>
#include"stock.hpp"

class group {
private:
    int N;
    int size;
    map<string, stock> stocks_map;
    vector<double> AAR;
    vector<double> CAAR;
public:
    group() {}
    group(int N_)
    {
        N = N_;
    }
    int get_size()
    {
        return size;
    }
    vector<double> GetAAR()
    {
        return AAR;
    };
    vector<double> GetCAAR()
    {
        return CAAR;
    }
    map<string, stock> get_map() {
        return stocks_map;
    }

    void cal_GetAAR(int N_);
    void cal_GetCAAR();

    void set_map(map <string, stock> &current_stock);// set the group with the current stock
};

