//
//  group.cpp
//  script
//
//  Created by Yipei Zhang on 12/10/21.
//

#include "group.hpp"

void group::set_map(map <string, stock>& current_stock)
{
    stocks_map = current_stock;
    size = (int) stocks_map.size();
}

void group::cal_GetAAR(int N_)
{
    size = (int) stocks_map.size();
    stock s;
    Vector v(2* N_+1);
    
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = 0;
    }
    for (map<string, stock>::iterator itr = stocks_map.begin(); itr != stocks_map.end(); itr++)
    {
        s = itr->second;

        v = v + s.get_ARIT();
    }
    AAR = v / size;

};
void group::cal_GetCAAR()
{
    
    CAAR.resize(2*N+1);
    CAAR[0] = AAR[0];

    for (int i=1; i< CAAR.size(); i++)
    {
        CAAR[i] = CAAR[i - 1] + AAR[i];

    }

    
};
