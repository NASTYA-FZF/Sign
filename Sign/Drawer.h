#pragma once

#include <afxwin.h>
#include <vector>
#include <amp_graphics.h>
#include "Work.h"

using namespace std;

class Drawer
{
	// ������������� ������� ���������.
	CRect frame;
	// ��������� �� ������ ����, ������� ���������.
	CWnd * wnd;
	// �������� ���������, ����������� � ������� ���������.
	CDC * dc;
	// �������� ���������, ����������� � ������.
	CDC memDC;
	// ������ ��� ��������� ��������� memDC.
	CBitmap bmp;
	// ���� ��� ������������ ��������� ������������� ������.
	bool init;
public:
	// ������������������� ������ ������ �� ������ HWND.
	void Create(HWND hWnd);

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin);

	double convert_range_d(double data, double outmax, double outmin, double inmax, double inmin);

	// ���������� ������.
	void DrawPoints(vector<double>& data, Signal sig, CString Ox, CString Oy, double data_x_max, double step_x);

	double MaxF(vector<double> y);

	double MinF(vector<double> y);

	void DrawTwoSig(vector<double>& data, vector<double>& data1, Signal sig, CString Ox, CString Oy, double data_x_max, double step_x);
};

