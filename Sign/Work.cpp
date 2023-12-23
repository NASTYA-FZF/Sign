#include "pch.h"
#define _USE_MATH_DEFINES
#include "Work.h"
#include <math.h>

Signal::Signal()
{
	a1 = 1;
	a2 = 0;
	a3 = 0;
	F1 = 1;
	F2 = 0;
	F3 = 0;
	fI1 = 3;
	fI2 = 0;
	fI3 = 0;
	Fd = 1000;
	n = 1024;
	sh.push_back(0);
}

Signal::Signal(double A1, double A2, double A3, double Ff1, double Ff2, double Ff3, double Fi1, double Fi2, double Fi3, double fD, int N)
{
	a1 = A1;
	a2 = A2;
	a3 = A3;
	F1 = Ff1;
	F2 = Ff2;
	F3 = Ff3;
	fI1 = Fi1;
	fI2 = Fi2;
	fI3 = Fi3;
	Fd = fD;
	n = N;
	sh.push_back(0);
}

vector<double> Signal::CreateVec()
{
	vector<double> zn;
	for (int i = 0; i < n; i++)
	{
		zn.push_back(FUNC(*this, i));
	}

	return zn;
}


const double TwoPi = 2 * M_PI;

//vector<double> Signal::fourea(vector<double> y)
//{
//// y - вектор анализируемых данных, Nvl - длина массива должна быть кратна степени 2.
//// FTvl - вектор полученных значений, Nft - длина массива должна быть равна Nvl.
//	vector<double> FTvl;
//	int Nvl(n), Nft(n);
//	int i, j, N, m, Mmax, Istp;
//	double Tmpr, Tmpi, Wtmp, Theta;
//	double Wpr, Wpi, Wr, Wi;
//	vector<double> Tmvl;
//
//	N = Nvl * 2;
//
//	for (i = 0; i < N; i += 2) 
//	{
//		Tmvl.push_back(0);
//		Tmvl.push_back(y[i / 2]);
//	}
//
//	i = 1; j = 1;
//	while (i < N) 
//	{
//		if (j > i) 
//		{
//			Tmpr = Tmvl[i]; Tmvl[i] = Tmvl[j]; Tmvl[j] = Tmpr;
//			Tmpr = Tmvl[i + 1]; Tmvl[i + 1] = Tmvl[j + 1]; Tmvl[j + 1] = Tmpr;
//		}
//		i = i + 2; m = Nvl;
//		while ((m >= 2) && (j > m)) 
//		{
//			j = j - m; m = m >> 1;
//		}
//		j = j + m;
//	}
//
//	Mmax = 2;
//	while (N > Mmax) 
//	{
//		Theta = -TwoPi / Mmax; Wpi = sin(Theta);
//		Wtmp = sin(Theta / 2); Wpr = Wtmp * Wtmp * 2;
//		Istp = Mmax * 2; Wr = 1; Wi = 0; m = 1;
//
//		while (m < Mmax) 
//		{
//			i = m; m = m + 2; Tmpr = Wr; Tmpi = Wi;
//			Wr = Wr - Tmpr * Wpr - Tmpi * Wpi;
//			Wi = Wi + Tmpr * Wpi - Tmpi * Wpr;
//
//			while (i < N) 
//			{
//				j = i + Mmax;
//				Tmpr = Wr * Tmvl[j] - Wi * Tmvl[j - 1];
//				Tmpi = Wi * Tmvl[j] + Wr * Tmvl[j - 1];
//
//				Tmvl[j] = Tmvl[i] - Tmpr; Tmvl[j - 1] = Tmvl[i - 1] - Tmpi;
//				Tmvl[i] = Tmvl[i] + Tmpr; Tmvl[i - 1] = Tmvl[i - 1] + Tmpi;
//				i = i + Istp;
//			}
//		}
//
//		Mmax = Istp;
//	}
//
//	for (i = 0; i < Nft; i++) 
//	{
//		j = i * 2; 
//		FTvl.push_back(2 * sqrt(pow(Tmvl[j], 2) + pow(Tmvl[j + 1], 2)) / Nvl);
//	}
//
//	return FTvl;
//}

double Signal::Es(vector<double> FUNC)
{
	double Esig(0);
	for (int i = 0; i < n; i++)
	{
		Esig += FUNC[i] * FUNC[i];
	}
	return Esig;
}

vector<double> Signal::shum()
{
	srand(time(NULL));
	vector<double> n0;
	for (int i = 0; i < n; i++)
	{
		n0.push_back((double)(rand()) / RAND_MAX * 2 - 1);
	}

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < n; j++)
		{
			n0[j] += (double)(rand()) / RAND_MAX * 2 - 1;
		}
	}
	
	return n0;
}

vector<double> Signal::bad_func(double al, vector<double> funct)
{
	vector<double> bad_sig;

	double SumSh(0);
	for (int k = 0; k < n; k++)
	{
		SumSh += sh[k] * sh[k];
	}

	double bet = sqrt(al * Es(funct) / SumSh);

	for (int i = 0; i < n; i++)
	{
		bad_sig.push_back(funct[i] + bet * sh[i]);
	}

	return bad_sig;
}

int Signal::f_porog(vector<double> bad_f, double g)
{
	double Esh = Es(bad_f), Econtr(0);
	for (int i = 0; i < n / 2; i++)
	{
		Econtr += bad_f[i] * bad_f[i] + bad_f[n - 1 - i] * bad_f[n - 1 - i];
		if (Econtr > g * Esh)
		{
			return i;
		}
	}
	return -1.0;
}

void Signal::fft(vector<base>& a, bool invert)
{
	int n = (int)a.size();
	if (n == 1)  return;

	vector<base> a0(n / 2), a1(n / 2);
	for (int i = 0, j = 0; i < n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * M_PI / n * (invert ? -1 : 1);
	base w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i < n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2, a[i + n / 2] /= 2;
		w *= wn;
	}
}

double FUNC(Signal s, int num)
{
	return s.a1 * sin(2 * M_PI * s.F1 * num / s.Fd + s.fI1) + s.a2 * sin(2 * M_PI * s.F2 * num / s.Fd + s.fI2) + s.a3 * sin(2 * M_PI * s.F3 * num / s.Fd + s.fI3);
}
