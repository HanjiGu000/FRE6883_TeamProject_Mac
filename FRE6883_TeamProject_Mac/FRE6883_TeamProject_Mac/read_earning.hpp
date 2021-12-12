//
//  read_earning.hpp
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
#include <algorithm>
#include <iomanip>
#include "curl/curl.h"
#include <fstream>
#include <map>
#include "global.hpp"
#include<stdlib.h>


using namespace std;
class test{
private:
    string ticker;
    int N;
    string annouce_date;
    double estimated;
    double reported;
    double surprise;
    double surprise_percentage;
    double absolute_surprise;
    vector<string> divide;
    vector<double> daily_return;
    vector<double> ARIT;
    const char* EarningFile = "EarningsAnnouncements.csv";
    
    
public:
    struct pair_data
    {
        string day_0;
        double estimate;
        double reported;
        double surprise;
        double surprise_percent;
        pair_data(): day_0(""), estimate(0.0), reported(0.0), surprise(0.0), surprise_percent(0.0){}
        pair_data(string day_0_, double estimate_, double reported_, double surprise_,
                  double surprise_percent_)
        :day_0(day_0_), estimate(estimate_),reported(reported_),surprise(surprise_),surprise_percent(surprise_percent_){}
        };
    map<string, pair_data> test1;
    map<string, double> surprice_percent_list;
    void set_ticker(int ticker_) {ticker = ticker_;}
    void set_annouce_date(int annouce_date_) {annouce_date = annouce_date_;}
    void set_reported(int reported_) {reported = reported_;}
    void set_surprise(int surprise_) {surprise = surprise_;}
    void set_surprise_percentage(int surprise_percentage_) {surprise_percentage = surprise_percentage_;}
    void set_estimated(int estimated_) {estimated = estimated_;}
    void set_absolute_surprise(double absolute_surprise_) {absolute_surprise = absolute_surprise_;}
    
    
    double get_absolute_surprise(){return absolute_surprise;}
    void populate_earnings_file(map<string, pair_data>& symbols);
    int WriteFile(string fname, map<string, pair_data> *m);
    void run();
    void divide_group(map<string, pair_data> &target);
    static bool cmp(const pair<string, int>& a, const pair<string, int>& b);
    string process_date(string date);
    
    map<string, pair_data> return_object(){return test1;}
};
