#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include "curl/curl.h"
#include <fstream>
#include <map>
#include <thread>


using namespace std;
const char* cIWB1000SymbolFile = "Russell_1000_component_stocks.csv";


void populateSymbolVector(vector<string>& symbols)
{
    ifstream fin;
    fin.open(cIWB1000SymbolFile, ios::in);
    string line, name, symbol;
    while (!fin.eof())
    {
        getline(fin, line);
        stringstream sin(line);
        getline(sin, symbol, ',');
        getline(sin, name);
        symbols.push_back(symbol);
    }
}


int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


struct MemoryStruct
{
    char *memory;
    size_t size;
};


void *myrealloc(void *ptr, size_t size)
{
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}


int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory)
    {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}


int main(void)
{
    vector<string> symbolList;
    // read Russell_1000_component_stocks.csv
    // and store symbols in a vector of string
    populateSymbolVector(symbolList);
    
    // file pointer to create file that store the data
    FILE* fp;
    const char resultfilename[FILENAME_MAX] = "Results.txt";
    
    // declaration of an object CURL
    CURL* handle;
    CURLcode result;
    
    // set up the program environment that libcurl needs
    curl_global_init(CURL_GLOBAL_ALL);
    
    // curl_easy_init() returns a CURL easy handle
    handle = curl_easy_init();
    
    // if everything's all right with the easy handle...
    if (handle)
    {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        
        // TODO: need to leave an endpoint for 2N - 1 interval
        string start_date = "2021-01-01";
        string end_date = "2021-11-30";
        
        //TODO: You must replace this API token with yours
        string api_token = "61a6cd6ff23426.12849192";
        
        vector<string>::iterator itr = symbolList.begin();
        for (; itr != symbolList.end(); itr++)
        {
            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;
            string symbol = *itr;
            string url_request = url_common + symbol + ".US?" + "from="
                                    + start_date + "&to=" + end_date + "&api_token="
                                    + api_token + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
       
            //adding a user agent
            curl_easy_setopt(handle, CURLOPT_USERAGENT,
                             "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            
            // "ab" append binary
            // fp is a pointer of FILE, to result.txt
            fp = fopen(resultfilename, "ab");
            fprintf(fp, "%s\n", symbol.c_str());
            
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
            result = curl_easy_perform(handle);
            fprintf(fp, "%c", '\n');
            fclose(fp);
            
            // check for errors
            if (result != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                return -1;
            }
            
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
            
            // perform, then store the expected code in result
            result = curl_easy_perform(handle);
            
            if (result != CURLE_OK)
            {
                // if errors have occured, tell us what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                return 1;
            }
            
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
            result = curl_easy_perform(handle);
            
            if (result != CURLE_OK)
            {
                // if errors have occurred, tell what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

                return 1;
            }
            
            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            cout << symbol << endl;
            while (getline(sData, line))
            {
                // if not found, the return value of find() will be string::npos
                size_t found = line.find('-');
                if (found != std::string::npos)
                {
                    cout<<line<<endl;
                    sDate = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    sValue = line.substr(line.find_last_of(',') + 1);
                    dValue = strtod(sValue.c_str(), NULL);
                    cout << sDate << " " << std::fixed << ::setprecision(2) << dValue << endl;
                }
            }
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
