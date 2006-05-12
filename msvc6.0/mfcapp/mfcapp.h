// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

// mfcapp.h : main header file for the MFCAPP application
//

#if !defined(AFX_MFCAPP_H__2CDE1D26_B146_11D7_B211_00C04F8906D8__INCLUDED_)
#define AFX_MFCAPP_H__2CDE1D26_B146_11D7_B211_00C04F8906D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcappApp:
// See mfcapp.cpp for the implementation of this class
//

class CMfcappApp : public CWinApp
{
public:
	CMfcappApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcappApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfcappApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCAPP_H__2CDE1D26_B146_11D7_B211_00C04F8906D8__INCLUDED_)
