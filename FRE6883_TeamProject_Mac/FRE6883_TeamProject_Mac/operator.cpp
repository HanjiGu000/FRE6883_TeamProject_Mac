//
//  operator.cpp
//  New_try
//
//  Created by Yipei Zhang on 12/12/21.
//
#include "operator.hpp"
#include <cmath>



Vector operator+(const Vector& V, const Vector& W)
{
    Vector a(V.size());
    if (V.size() != W.size())
    {
        cout << "Vector operator + Dimension Errors" << endl;
        cout << "Vector 1.size: " << V.size() << endl;
        cout << "Vector 2.size: " << W.size() << endl;
        return a;
    }
    int d = V.size();

    for (int j = 0; j < d; j++) a[j] = V[j] + W[j];
    return a;
}

Vector operator-(const Vector& V, const Vector& W)
{
    Vector a(V.size());
    if (V.size() != W.size())
    {
        cout << "Vector operator- Dimension Errors" << endl;
        cout << "Vector 1.size: " << V.size() << endl;
        cout << "Vector 2.size: " << W.size() << endl;
        return a;
    }
    int d = V.size();
   
    
    for (int j = 0; j < d; j++)
    {
        
        a[j] = V[j] - W[j];
    }
    return a;
}

double operator*(const Vector& V, const Vector& W)
{
    double sum = -1000000000;
    if (V.size() != W.size())
    {
        cout << "Vector operator * Dimension Errors" << endl;
        cout << "Vector 1.size: " << V.size() << endl;
        cout << "Vector 2.size: " << W.size() << endl;
        return sum;
    }
    sum = 0;
    int d = V.size();
    
    for (int j = 0; j < d; j++)
    {
        sum = sum + V[j] * W[j];

    }
        
    
    return sum;
}
Vector operator&(const Vector& V, const Vector& W)
{
    Vector a(V.size());
    if (V.size() != W.size())
    {
        cout << "Vector operator & Dimension Errors" << endl;
        cout << "Vector 1.size: " << V.size() << endl;
        cout << "Vector 2.size: " << W.size() << endl;
        return a;
    }
    int d = V.size();
    
    for (int j = 0; j < d; j++)
    {
        a[j] = a[j] + V[j] * W[j];
    }
        
    
    return a;
}


Vector operator*( const Vector& W, const double& a)
{
    int d = W.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = a * W[j];
    return U;
}
Vector operator*(const Vector& W, const int& a)
{
    int d = W.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = a * W[j];
    return U;
}
Vector operator/( const Vector& W, const double& a)
{
    int d = W.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] =  W[j]/a;
    return U;
}
Vector operator/(const Vector& W, const int& a)
{
    int d = W.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = W[j] / a;
    return U;
}


Vector operator^(const Vector& V, const double& a)
{
    int d = V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = pow(V[j] ,a);
    return U;
}

ostream& operator<<(ostream& out, Vector& V)
{
    int N = (V.size() - 1) / 2;
    out << "N" << "     " << "Value" << endl;
    for (int itr = 0; itr < V.size(); itr++)
        out << itr - N << "   "  << V[itr] << endl;
    out << endl;
    return out;
}

ostream& operator<<(ostream& out, Matrix& W)
{
    for (int i = 0; i < W[0].size(); i++) {
        int N = (W[0].size() - 1) / 2;
        out << i - N;
        for (int itr = 0; itr < W.size(); itr++)
            out << "   " << setprecision(6) << W[itr][i];
        out << endl;
    }
    out << endl;
    return out;
}

ostream& operator<<(ostream& out, vector<Matrix>& W)
{
    
    for (vector<Matrix>::iterator itr = W.begin(); itr != W.end(); itr++)
    {
        out << *itr;
        out << endl;
        out << endl;
    }
        
    out << endl;
    return out;
}
