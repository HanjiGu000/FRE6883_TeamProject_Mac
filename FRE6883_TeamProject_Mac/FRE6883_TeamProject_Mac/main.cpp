//
//  main.cpp
//  script
//
//  Created by Yipei Zhang on 12/4/21.
//
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <thread>
#include <iomanip>
#include "curl/curl.h"
#include <fstream>
#include <map>
#include "Libcurl.hpp"
#include "global.hpp"
#include "test.hpp"
#include "stock.hpp"
//#include "CalcDate.hpp"
#include "operator.hpp"

using namespace std;

void input_N(global_constant& g)
{


    int N_;
    cout << "Please input N" << endl;
    cin >> N_;
    while ((N_ < 30) || ((N_ > 60)))
    {
        cout << "N should be greater than 30 and less than 60" << endl;
        cout << "Please continue to input N" << endl;
        cin >> N_;
    }
    g.N_days = N_;
}


int main()
{
    //global_constant g;
    //input_N(g);
//    test mytest;
//    mytest.run();
//    
//    map<string, test::pair_data> store;
//    store = mytest.return_object();
//    
//    stock one_stock(store.begin()->first);
//    
    download();
    return 0;
}

