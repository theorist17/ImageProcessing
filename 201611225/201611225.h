
// 201611225.h : main header file for the 201611225 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy201611225App:
// See 201611225.cpp for the implementation of this class
//

class CMy201611225App : public CWinApp
{
public:
	CMy201611225App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy201611225App theApp;
