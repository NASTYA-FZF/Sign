#pragma once

#include <afxwin.h>
#include <vector>
#include <amp_graphics.h>
#include "Work.h"

using namespace std;

class Drawer
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, обалсти рисования.
	CWnd * wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC * dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd);

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin);

	double convert_range_d(double data, double outmax, double outmin, double inmax, double inmin);

	// Нарисовать сигнал.
	void DrawPoints(vector<double>& data, Signal sig, CString Ox, CString Oy, double data_x_max, double step_x);

	double MaxF(vector<double> y);

	double MinF(vector<double> y);

	void DrawTwoSig(vector<double>& data, vector<double>& data1, Signal sig, CString Ox, CString Oy, double data_x_max, double step_x);
};

