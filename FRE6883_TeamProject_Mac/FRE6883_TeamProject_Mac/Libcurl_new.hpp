//
//  Libcurl_new.hpp
//  New_try
//
//  Created by Yipei Zhang on 12/12/21.
//
#pragma once
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
#include"stock.hpp"
#include "ParseDate.hpp"
#include<map>
#include <stdio.h>


//const char* cIWB1000SymbolFile1 = "EarningsAnnouncements.csv";
using namespace std;


int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


struct MemoryStruct {
    char* memory;
    size_t size;
};


void populateSymbolVector(map<string, stock>& symbols, string Filename, int Nday)
{
    ifstream fin;
    fin.open(Filename, ios::in);
    string line, symbol, announce_date, estimated, reported, surprise, surprise_percentage;
    double destimated, dreported, dsurprise, dsurprise_percentage;
    while(!fin.eof())
    {
        getline(fin,line);
        stringstream sin(line);
        getline(sin, symbol, ' ');
        getline(sin, announce_date, ' ');
        getline(sin, estimated, ' ');
        getline(sin, reported, ' ');
        getline(sin, surprise, ' ');
        getline(sin, surprise_percentage, ' ');
        destimated = strtod(estimated.c_str(), NULL);
        dreported = strtod(reported.c_str(), NULL);
        dsurprise = strtod(surprise.c_str(), NULL);
        dsurprise_percentage = strtod(surprise_percentage.c_str(), NULL);
        
        if (symbol == "ticker")
            continue;
        stock curr_stock = stock(symbol, announce_date, destimated, dreported, dsurprise, dsurprise_percentage, Nday);
        symbols[symbol] = curr_stock;
    }
}


void* myrealloc(void* ptr, size_t size)
{
    /*
    There might be a realloc() out there that doesn't like reallocting
    NULL pointers, so we take care of it here
     */
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}


int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)data;
    mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}


int download(stock &stock, string start, string end)
{
    // declaration of an object CURL
    CURL* handle;
    CURLcode result;
    
    //set up the program environment that libcurl needs
    curl_global_init(CURL_GLOBAL_ALL);
    
    //curl_easy_init() reutrns a CURL easy handle
    handle = curl_easy_init();
    
    //if everything's all right with the easy handle
    if(handle)
    {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        string start_date = start;
        string end_date = end;
        // you must replace this API token with yours
        string api_token = "61a6cd6ff23426.12849192";
        
        struct MemoryStruct data;
        data.memory = NULL;
        data.size = 0;
        string symbol = stock.get_ticker();
        auto p = symbol.find('\r');
        
       if ( p != symbol.npos )
       {
           symbol.replace(p, 1, "");
       }
        string url_request = url_common + symbol + ".US?" + "from="
            + start_date + "&to=" + end_date + "&api_token="
            + api_token + "&period=d";
        
        curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

        //adding a user agent
        curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(handle,CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

        // perform, then store the expected code in result
        result = curl_easy_perform(handle);

        if (result != CURLE_OK)
        {
        // if errors have occured, tell us what is wrong with result
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(result));
            return -1;
        }
        map<string, double> price;
        stringstream sData;
        sData.str(data.memory);
        string sValue, sDate;
        double dValue = 0;
        string line;

            
        while (getline(sData, line))
        {
            size_t found = line.find('-');
            if (found != std::string::npos)
            {
                sDate = line.substr(0, line.find_first_of(','));
                line.erase(line.find_last_of(','));
                sValue = line.substr(line.find_last_of(',') + 1);
                dValue = strtod(sValue.c_str(), NULL);
                price[sDate] = dValue;
            }
        }
        stock.update_price(price);
            
        free(data.memory);
        data.size = 0;
    }
    
    else
    {
        fprintf(stderr, "Curl init failed!\n");
        return -1;
    }
    // cleanup since you've used curl_easy_init
    curl_easy_cleanup(handle);

    // release resources acquired by curl_global_init()
    curl_global_cleanup();

    return 0;
}


int download2(map<string, stock>& symbolList)
{
    // declaration of an object CURL
    CURL* handle;
    CURLcode result;
    
    //set up the program environment that libcurl needs
    curl_global_init(CURL_GLOBAL_ALL);
    
    //curl_easy_init() reutrns a CURL easy handle
    handle = curl_easy_init();
    
    //if everything's all right with the easy handle
    if(handle)
    {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        
        // you must replace this API token with yours
        string api_token = "61a6cd6ff23426.12849192";
        map<string,stock>::iterator itr = symbolList.begin();
        int N = itr->second.get_N();
        for (; itr != symbolList.end(); itr++)
        {
            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;
            
            string symbol = itr->first;
            string EAD = itr->second.get_annouce_date();
            string start_date;
            string end_date;
            CalcMinMaxDate(EAD, N, start_date, end_date);
            
            auto p = symbol.find('\r');
            if ( p != symbol.npos )
            {
               symbol.replace(p, 1, "");
            }
            
            string url_request = url_common + symbol + ".US?" + "from="
                + start_date + "&to=" + end_date + "&api_token="
                + api_token + "&period=d";
            
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

            //adding a user agent
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle,CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

            // perform, then store the expected code in result
            result = curl_easy_perform(handle);

            if (result != CURLE_OK)
            {
            // if errors have occured, tell us what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(result));
                return -1;
            }
            
            map<string, double> price;
            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            vector<string> tempDates;
            vector<double> tempHistPrice;

            
            while (getline(sData, line))
            {
                size_t found = line.find('-');
                if (found != std::string::npos)
                {
                    sDate = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    sValue = line.substr(line.find_last_of(',') + 1);
                    dValue = strtod(sValue.c_str(), NULL);
                    tempDates.push_back(sDate);
                    tempHistPrice.push_back(dValue);
                }
            }
            auto it = find(tempDates.begin(), tempDates.end(), EAD);
            if (it!= tempDates.end())
            {
                int index = it-tempDates.begin();
                for (int k = -N; k<=N; k++)
                {
                    price[tempDates[index+k]]= tempHistPrice[index+k];
                }
            }
            
            itr -> second.update_price(price);
//            cout << itr->first << endl;
            free(data.memory);
            data.size = 0;
        }
    }
    else
    {
        fprintf(stderr, "Curl init failed!\n");
        return -1;
    }
    // cleanup since you've used curl_easy_init
    curl_easy_cleanup(handle);

    // release resources acquired by curl_global_init()
    curl_global_cleanup();

    return 0;
}


void ParseIntoMap(map<string, stock>& symbols, string FileName, int Nday)
{
    populateSymbolVector(symbols,FileName, Nday);
    download2(symbols);
}


