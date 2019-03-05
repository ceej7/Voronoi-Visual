
// Voronoi-Visual.h : main header file for the Voronoi-Visual application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVoronoiVisualApp:
// See Voronoi-Visual.cpp for the implementation of this class
//

class CVoronoiVisualApp : public CWinApp
{
public:
	CVoronoiVisualApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVoronoiVisualApp theApp;
