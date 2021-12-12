//
//  read_earning.cpp
//  New_try
//
//  Created by Yipei Zhang on 12/10/21.
//


#include "read_earning.hpp"
#include <cstring>

using namespace std;
    
    bool test::cmp(const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    }
    
     void test::populate_earnings_file(map<string, pair_data>& symbols)
    {
         
         ifstream fin;
         fin.open(EarningFile, ios::in);
         string line,ticker,date,period_ending,estimate, reported, surprise, surprise_percent;
         while(!fin.eof())
         {
             int num = 0;
             if (num == 10)
                 break;
             num +=1;
            getline(fin,line);
            stringstream sin(line);
            getline(sin, ticker, ',');
            getline(sin, date, ',');
            getline(sin, period_ending, ',');
            getline(sin, estimate, ',');
            getline(sin, reported, ',');
            getline(sin, surprise, ',');
            getline(sin, surprise_percent, ',');
            
            if (ticker.length()<1 or ticker == "ticker")
                continue;
            string date_new;
            date_new = process_date(date);
            surprice_percent_list[ticker] = atof(surprise_percent.c_str());
            symbols[ticker] = pair_data(date_new, atof(estimate.c_str()), atof(reported.c_str()),atof(surprise.c_str()),atof(surprise_percent.c_str()));
         }
    }
    string test::process_date(string date){
        string input = date;
        vector<string> vect;
        stringstream ss(input);
        
        string output;
        
        while( ss.good() )
        {
            string substr;
            getline( ss, substr, '-' );
            vect.push_back( substr );
        }
        if (vect[1] == "Jan")
            vect[1] = "01";
        else if (vect[1] == "Feb")
            vect[1] = "02";
        else if (vect[1] == "Mar")
            vect[1] = "03";
        else if (vect[1] == "Apr")
            vect[1] = "04";
        else if (vect[1] == "May")
            vect[1] = "05";
        else if (vect[1] == "Jun")
            vect[1] = "06";
        else if (vect[1] == "Jul")
            vect[1] = "07";
        else if (vect[1] == "Aug")
            vect[1] = "08";
        else if (vect[1] == "Sep")
            vect[1] = "09";
        else if (vect[1] == "Oct")
            vect[1] = "10";
        else if (vect[1] == "Nov")
            vect[1] = "11";
        else if (vect[1] == "Dec")
            vect[1] = "12";
        
        if (vect[0].length() == 1)
            vect[0] = "0" + vect[0];
        output = "20" + vect[2] + "-" + vect[1] + "-" + vect[0];
        return output;
    }
        
    void test::divide_group(map<string, pair_data> &target){
        vector<pair<string, double>> vec(surprice_percent_list.begin(), surprice_percent_list.end());
        sort(vec.begin(), vec.end(),cmp);

        
        double first_divide = vec[(int)(vec.size()/3)].second;
        double second_divide = vec[(int)(2*vec.size()/3)].second;
        map<string, pair_data> miss_stocks;
        map<string, pair_data> meat_stocks;
        map<string, pair_data> beat_stocks;
        
        for(const auto &any : target){
            if (any.second.surprise_percent < first_divide)
            {
                miss_stocks[any.first] = pair_data(any.second.day_0,any.second.estimate, any.second.reported, any.second.surprise, any.second.surprise_percent);
            }
            else if (any.second.surprise_percent < second_divide)
            {
                meat_stocks[any.first] = pair_data(any.second.day_0,any.second.estimate, any.second.reported, any.second.surprise, any.second.surprise_percent);
            }
            else
            {
                beat_stocks[any.first] = pair_data(any.second.day_0,any.second.estimate, any.second.reported, any.second.surprise, any.second.surprise_percent);
            }
        }
        WriteFile("miss_stocks.txt", &miss_stocks);
        WriteFile("meet_stocks.txt", &meat_stocks);
        WriteFile("beat_stocks.txt", &beat_stocks);
        
    }
        
        
    int test::WriteFile(string fname, map<string, pair_data> *m) {
        int count = 0;
        if (m->empty())
            return 0;
        FILE *fp = fopen(fname.c_str(), "w");
        for(map<string, pair_data>::iterator it = m->begin(); it != m->end(); it++) {
            fprintf(fp, "%s %s %s %s %s %s\n", it->first.c_str(),it -> second.day_0.c_str(),to_string(it->second.estimate).c_str(),to_string(it->second.reported).c_str(),to_string(it->second.surprise).c_str(),to_string(it->second.surprise_percent).c_str());
            //it->second.day_0.c_str()
            count++;
            }
        fclose(fp);
        return count;
    };
    
    void test::run(){
    
        populate_earnings_file(test1);
        WriteFile("Earning_info.txt", &test1);
        divide_group(test1);
    }
    
    

