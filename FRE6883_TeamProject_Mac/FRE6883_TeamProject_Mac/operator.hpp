//
//  operator.hpp
//  New_try
//
//  Created by Yipei Zhang on 12/10/21.
#pragma once


#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;
typedef vector<Matrix> Matrix_all;


Vector operator+(const Vector& V, const Vector& W);
Vector operator-(const Vector& V, const Vector& W);
double operator*(const Vector& V, const Vector& W);
// add operator&, this is for vector multiplication
Vector operator&(const Vector& V, const Vector& W);


Vector operator*(const Vector& W, const double& a);
Vector operator/(const Vector& W, const double& a);
Vector operator/(const Vector& W, const int& a);
Vector operator*( const Vector& W, const int& a);
Vector operator^(const Vector& V, const double& a);


ostream& operator<<(ostream& out, Vector& V);
ostream& operator<<(ostream& out, Matrix& W);
ostream& operator<<(ostream& out, vector<Matrix> & W);




