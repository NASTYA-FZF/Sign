
// Sign.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CSignApp:
// Сведения о реализации этого класса: Sign.cpp
//

class CSignApp : public CWinApp
{
public:
	CSignApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSignApp theApp;
