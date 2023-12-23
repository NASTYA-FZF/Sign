
// SignDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Sign.h"
#include "SignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CSignDlg



CSignDlg::CSignDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIGN_DIALOG, pParent)
	, A1(4)
	, f1(20)
	, fi1(5)
	, A2(0)
	, f2(0)
	, fi2(0)
	, A3(0)
	, f3(0)
	, fi3(0)
	, fd(1000)
	, N(512)
	, alpha(0.1)
	, gamma(0.9)
	, Eotkl(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT2, f1);
	DDX_Text(pDX, IDC_EDIT3, fi1);
	DDX_Text(pDX, IDC_EDIT4, A2);
	DDX_Text(pDX, IDC_EDIT6, f2);
	DDX_Text(pDX, IDC_EDIT10, fi2);
	DDX_Text(pDX, IDC_EDIT5, A3);
	DDX_Text(pDX, IDC_EDIT7, f3);
	DDX_Text(pDX, IDC_EDIT11, fi3);
	DDX_Text(pDX, IDC_EDIT9, fd);
	DDX_Text(pDX, IDC_EDIT8, N);
	DDX_Text(pDX, IDC_EDIT12, alpha);
	DDX_Text(pDX, IDC_EDIT13, gamma);
	DDX_Text(pDX, IDC_EDIT14, Eotkl);
	DDX_Control(pDX, IDC_EDIT14, Eotklctrl);
}

BEGIN_MESSAGE_MAP(CSignDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSignDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSignDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CSignDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CSignDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Обработчики сообщений CSignDlg

BOOL CSignDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drv.Create(GetDlgItem(IDC_STARTPIC)->GetSafeHwnd());

	drv_spec.Create(GetDlgItem(IDC_SPECPIC)->GetSafeHwnd());

	drv_shum.Create(GetDlgItem(IDC_SHUM)->GetSafeHwnd());

	drv_shspec.Create(GetDlgItem(IDC_SHUMSPEC)->GetSafeHwnd());

	drv_clearing.Create(GetDlgItem(IDC_CLEARPIC)->GetSafeHwnd());

	drv_sravn.Create(GetDlgItem(IDC_SRAV)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

Signal sig;
vector<double> func, bad_f, spec_bad;
vector<base> spec_shum;

void CSignDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);
	Signal s (A1, A2, A3, f1, f2, f3, fi1, fi2, fi3, fd, N);
	sig = s;

	func = sig.CreateVec();
	drv.DrawPoints(func, sig, L"t", L"x", sig.n / sig.Fd, 1 / sig.Fd);
	
	vector<base> specf(func.begin(), func.end());
	sig.fft(specf, true);
	vector<double> spec_d;

	for (int i = 0; i < specf.size(); i++)
	{
		spec_d.push_back(sqrt(specf[i].real() * specf[i].real() + specf[i].imag() * specf[i].imag()));
	}

	drv_spec.DrawPoints(spec_d, sig, L"f", L"|X|", sig.Fd, sig.Fd / sig.n);
}


void CSignDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);

	if (spec_bad.size() != 0 || spec_shum.size() != 0)
	{
		spec_bad.clear();
		spec_shum.clear();
	}

	sig.sh.clear();
	sig.sh = sig.shum();

	bad_f = sig.bad_func(alpha, func);

	drv_shum.DrawPoints(bad_f, sig, L"t", L"x", sig.n / sig.Fd, 1 / sig.Fd);

	vector<base> spec(bad_f.begin(), bad_f.end());

	sig.fft(spec, true);

	spec_shum = spec;

	vector<double> spec_d;

	for (int i = 0; i < spec.size(); i++)
	{
		spec_d.push_back(sqrt(spec[i].real() * spec[i].real() + spec[i].imag() * spec[i].imag()));
	}

	spec_bad = spec_d;

	drv_shspec.DrawPoints(spec_d, sig, L"f", L"|X|", sig.Fd, sig.Fd / sig.n);

	spec_d.clear();
	spec.clear();
}


void CSignDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void CSignDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений

	UpdateData(true);

	vector<base> need = spec_shum;

	if (gamma != 1.)
	{
		int por = sig.f_porog(spec_bad, gamma);
		base nol(0., 0.);
		for (int i = por; i < sig.n - por; i++)
		{
			spec_shum[i] = nol;
		}
	}

	vector<double> spect_obr;
	for (int i = 0; i < spec_shum.size(); i++)
	{
		spect_obr.push_back(sqrt(spec_shum[i].real() * spec_shum[i].real() + spec_shum[i].imag() * spec_shum[i].imag()));
	}

	drv_shspec.DrawTwoSig(spec_bad, spect_obr, sig, L"f", L"|X|", sig.Fd, sig.Fd / sig.n);

	vector<double> clear_f, imf;

	sig.fft(spec_shum, false);
	for (int i = 0; i < spec_shum.size(); i++)
	{
		clear_f.push_back(spec_shum[i].real());
		imf.push_back(spec_shum[i].imag());
	}

	drv_clearing.DrawPoints(clear_f, sig, L"t", L"x", sig.n / sig.Fd, 1 / sig.Fd);

	drv_sravn.DrawTwoSig(func, clear_f, sig, L"t", L"x", sig.n / sig.Fd, 1 / sig.Fd);

	vector<double> srav;
	for (int i = 0; i < func.size(); i++)
	{
		srav.push_back(clear_f[i] - func[i]);
	}

	double E = 100 * sig.Es(srav) / sig.Es(func);
	CString str;
	str.Format(L"%.2f", E);
	Eotklctrl.SetWindowTextW(str);


	spect_obr.clear();
	clear_f.clear();

	spec_shum = need;
	need.clear();
}
