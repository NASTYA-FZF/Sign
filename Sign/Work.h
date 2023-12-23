#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <complex>
using namespace std;

typedef complex<double> base;

class Signal
{
	double a1, a2, a3, F1, F2, F3, fI1, fI2, fI3;

public:

	vector<double> sh;
	double Fd;
	int n;

	Signal();
	Signal(double, double, double, double, double, double, double, double, double, double, int);
	vector<double> CreateVec();
	friend double FUNC(Signal s, int num);
	vector<double> fourea(vector<double> y);
	double Es(vector <double>);
	vector <double> shum();
	//double betta(double, vector<double>);
	vector<double> bad_func(double, vector<double>);
	int f_porog(vector<double>, double);
	void fft(vector<base>& a, bool invert);
};