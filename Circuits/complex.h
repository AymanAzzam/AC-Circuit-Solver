#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <complex>

class Complex
{
	vector<string> Names;
	vector<double> Real;
	vector<double> Imag;
	double w;
	void transform();
public:
	Complex(vector<string>,vector<double>,vector<double>,double);
	complex<double>value[15];
	~Complex();
	void approx(double&);
};