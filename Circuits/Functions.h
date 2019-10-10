#pragma once

#include <Eigen/Eigen>
#include <complex>
#include <iostream>
using namespace std;
using namespace Eigen;

void intialize(MatrixXcd&,int ,int);
void merge(MatrixXcd&,MatrixXcd&,MatrixXcd&,MatrixXcd&,MatrixXcd&,int,int);
void transformation(complex<double> x,double& w,double & m);
void approx(double&);
