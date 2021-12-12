#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <thread>
#include <iomanip>
#include <fstream>
#include <map>
#include <ctime>
#include <time.h>

using namespace std;

//const char* Result = "Results.txt";


// print and return the current date in the form of YYYY-MM-DD
string GetCurrDate()
{
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    auto str = oss.str();
    
    cout << str << endl;
    return str;
}


string getTimeinSec(string Time)
{
    tm t = { 0 };
    istringstream ssTime(Time);
    char time[100];
    memset(time, 0, 100);
    
    if (ssTime >> get_time(&t, "%Y-%m-%d"))
    {
        sprintf(time, "%ld", mktime(&t));
        return string(time);
    }
    else
    {
        cout << "Parse failed\n";
        return "";
    }
}


void CalcMinMaxDate(string Time, int N, string &startDate, string &endDate)
{
    double post_dDate = strtod(getTimeinSec(Time).c_str(), NULL) + 86400 * 1.8 * N;
    double pre_dDate = strtod(getTimeinSec(Time).c_str(), NULL) - 86400 * 1.8 * N;
    
    time_t start = pre_dDate;
    time_t end = post_dDate;
    
    auto start_d = *localtime(&start);
    auto end_d = *localtime(&end);

    char buffer1[80];
    char buffer2[80];
    
    strftime(buffer1, 80, "%F", &start_d);
    strftime(buffer2, 80, "%F", &end_d);
    
    startDate = buffer1;
    endDate = buffer2;
    
}
