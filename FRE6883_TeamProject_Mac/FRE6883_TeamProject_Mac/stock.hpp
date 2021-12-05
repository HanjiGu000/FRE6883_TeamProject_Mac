//
//  stock.hpp
//  FRE6883_TeamProject_Mac
//
//  Created by Hanji Gu on 12/4/21.
//

#ifndef stock_hpp
#define stock_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class stock
{
private:
    // store data from EarningsAccouncement file
    string ticker;
    string annouce_date;
    double estimate;
    double reported;
    double suprise;
    double suprise_pct;

    // store bootstraping data
    vector<double> price;
    vector<double> daily_return;
    vector<double> abn_Rit;
    
public:
    // constructor with parameter
    stock(string ticker_, string annouce_date_, double estimate_,
          double reported_, double suprise_, double suprise_pct_)
    :ticker(ticker_), annouce_date(annouce_date_), estimate(estimate_),
    reported(reported_), suprise(suprise_), suprise_pct(suprise_pct_) {}
    
    // Get functions
    vector<double> Get_Price() { return price; }
    vector<double> Get_Return() { return daily_return; }
    vector<double> Get_Abn_Rit() { return abn_Rit; }
    double Get_estimate() { return estimate; }
    double Get_retported() { return reported; }
    double Get_suprise() { return suprise; }
    double Get_suprise_pct() { return suprise_pct; }
    
    void Calc_Return();
    void Calc_Abn_Rit();
    
    // TODO: To Be Continue
};

#endif /* stock_hpp */
