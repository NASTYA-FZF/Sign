
// SignDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"

// Диалоговое окно CSignDlg
class CSignDlg : public CDialogEx
{
// Создание
public:
	CSignDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIGN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double A1;
	double f1;
	double fi1;
	double A2;
	double f2;
	double fi2;
	double A3;
	double f3;
	double fi3;
	double fd;
	int N;
	Drawer drv;
	Drawer drv_spec;
	afx_msg void OnBnClickedOk();
	double alpha;
	Drawer drv_shum;
	double gamma;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	Drawer drv_shspec;
	Drawer drv_clearing;
	Drawer drv_sravn;
	afx_msg void OnBnClickedButton2();
	double Eotkl;
	CEdit Eotklctrl;
};
