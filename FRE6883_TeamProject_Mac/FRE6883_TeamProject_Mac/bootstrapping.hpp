//
//  bootstrapping.hpp
//  New_try
//
//  Created by Yipei Zhang on 12/12/21.
//
#include <map>
#include <string>
#include <vector>

#include "stock.hpp"
#include "global.hpp"
#include "shuffle_stock.hpp"

using namespace std;

vector<vector<double>> output_one_sample(vector<vector<double>> &output, global_constant &g, string key){
    
    // change all 190 to 2*g.get_N()+1 or initialize int price_len = 2*g.get_N()+1; first
    
    //vector<vector<string>> one_sample_together;
    vector<string> one_sample;// this is stock name list for one time
    vector<double> AARt(g.get_N()*2+1); // storing AARt for one sample
    vector<double> average_AARt(g.get_N()*2+1); // storing final AARt
    vector<double> AAR_std(g.get_N()*2+1); // calculating AAR-std
    vector<double> CAAR(g.get_N()*2+1); // storing final CAAR
    vector<double> CAAR_std(g.get_N()*2+1); // calculating CAAR-std
    
    // these two are for calculating standard deviation
    vector<vector<double>> AARt_group;
    vector<vector<double>> CAAR_group;

    map<string, stock> clean_price;
    // check whether the stock does not have enough prices, delete those which do not have 2N+1
    if (key == "miss") clean_price = g.check_size(g.MissSymbols);
    else if (key == "meet") clean_price = g.check_size(g.MeetSymbols);
    else if (key == "beat") clean_price = g.check_size(g.BeatSymbols);
    
    for(int i = 0; i < 40; i++)
    {
        one_sample = random(key, clean_price, 80);
        //one_sample_together.push_back(one_sample);
        
        vector<vector<double>> AARmt;
        for(int i = 0; i < one_sample.size(); i++)
        {
            vector<double> target = g.global_stock[one_sample[i]].get_ARIT();
            AARmt.push_back(target);
        }
        // get average AARt for one sample
        // change 190 to 2*g.get_N()+1
        vector<double> AARt(g.get_N()*2+1);
        for(int i = 0; i < AARmt.size(); i ++)
        {
            AARt = AARt + AARmt[i];
        }
        AARt = AARt / 80;
        AARt_group.push_back(AARt);
        average_AARt = average_AARt + AARt;
        // get CAAR for one sample
        double sum = 0;
        vector<double> CAAR_one;
        for (int i = 0; i < AARt.size(); i++)
        {
            sum += AARt[i];
            CAAR_one.push_back(sum);
        }
        CAAR = CAAR + CAAR_one;
        CAAR_group.push_back(CAAR_one);
    }
    // get average CAAR and AARt for the whole group
    CAAR = CAAR / 40;
    average_AARt = average_AARt / 40;

    // compute AAR-std
    for(int i = 0; i < AARt_group.size(); i ++)
    {
        vector<double> minus_mean = (AARt_group[i] - average_AARt);
        AAR_std = AAR_std + minus_mean & minus_mean;
    }
    AAR_std = AAR_std/40;
    for(int i = 0; i < AAR_std.size();i++)
    {
        AAR_std[i] = sqrt(AAR_std[i]);
    }
    // compute AAR-std
    for(int i = 0; i < CAAR_group.size(); i ++)
    {
        vector<double> minus_mean = (CAAR_group[i] - CAAR);
        CAAR_std = CAAR_std + minus_mean & minus_mean;
    }
    CAAR_std = CAAR_std/40;
    for(int i = 0; i < AAR_std.size();i++)
    {
        CAAR_std[i] = sqrt(CAAR_std[i]);
    }
    // save information with order
    output.push_back(average_AARt);
    output.push_back(AAR_std);
    output.push_back(CAAR);
    output.push_back(CAAR_std);
    cout << "done bootstrapping and calculating for one group" << endl;
    return output;
}
    





