//
//  stock.hpp
//  New_try
//
//  Created by Yipei Zhang on 12/10/21.
//

#pragma once
#include<string>
#include<iostream>
#include "operator.hpp"
#include<vector>
#include<map>
using namespace std;

class stock
{
private:
    string ticker;
    int N;
    string annouce_date;
    double estimated;
    double reported;
    double surprise;
    double surprise_percentage;
    map<string, double> price;
    map<string,double> daily_return;
    vector<double> ARIT;
public:
    stock() {}
    stock(string ticker_) { ticker = ticker_; }
    stock(string ticker_, string annouce_date_, double estimated_, double reported_, double surprise_, double surprise_percentage_, int N_)
    {
        ticker = ticker_; annouce_date = annouce_date_; estimated = estimated_; reported = reported_; surprise = surprise_; surprise_percentage = surprise_percentage_; N = N_;
    }
    stock(string ticker_, int N_) { ticker = ticker_; N = N_; }
    map<string, double> cal_return();
    map<string, double> get_return() {
        return daily_return;
    }
    map<string, double> get_price() {
        return price;
    }
    int get_N() {
        return N;
    }
    string get_annouce_date() {
        return annouce_date;
    }
    double get_estimated() {
        return estimated;
    }

    double get_reported() { return reported; }
    double get_surprise() { return surprise; }
    double get_surprise_percentage() { return surprise_percentage; }

    void cal_ARIT(stock IWB);
    vector<double> get_ARIT() {
        return ARIT;
    }
    map<string, double> get_benchmark();
    string get_ticker()
    {
        return ticker;
    }
    void update_price(map<string, double> price_update)

    {
        price = price_update;
    }


    void set_N(int N_) {
        N = N_;

    }
};

