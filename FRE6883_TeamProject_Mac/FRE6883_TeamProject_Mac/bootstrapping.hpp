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

vector<vector<double>> output_one_sample(global_constant &g, string key){
            
    vector<vector<string>> one_sample_together;
    vector<string> one_sample;
    vector<double> AARt(148);
    vector<double> average_AARt(148);
    vector<double> CAAR;
    vector<vector<double>> output_info;
    //double aart;
    for(int i = 0; i < 40; i++)
    {
        one_sample_together.push_back(random(key, g, 80));
        one_sample = random(key, g, 80);
        vector<vector<double>> AARmt;
        for(int i = 0; i < one_sample.size(); i++)
        {
            vector<double> target = g.global_stock[one_sample[i]].get_ARIT();
            AARmt.push_back(target);
        }
        
        vector<double> AARt(148);
        for(int i = 0; i < AARmt.size(); i ++)
        {
            AARt = AARt + AARmt[i];
        }
        AARt = AARt / 80;
        average_AARt = average_AARt + AARt;
    }
    average_AARt = average_AARt / 40;
    
    //AARt = one_group / g.group_size;
    double sum = 0;
    for (vector<double>::iterator itr = average_AARt.begin(); itr != average_AARt.end(); itr ++)
    {
        sum += *itr;
        CAAR.push_back(sum);
    }
    
    output_info.push_back(average_AARt);
    output_info.push_back(CAAR);
    cout << "done bootstrapping and calculating for one group" << endl;
    return output_info;
}
    





