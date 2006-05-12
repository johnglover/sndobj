// mfcapp2.h : main header file for the MFCAPP2 application
//

#if !defined(AFX_MFCAPP2_H__AFC9C446_A781_428F_85AB_52A683D949AB__INCLUDED_)
#define AFX_MFCAPP2_H__AFC9C446_A781_428F_85AB_52A683D949AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcapp2App:
// See mfcapp2.cpp for the implementation of this class
//

class CMfcapp2App : public CWinApp
{
public:
	CMfcapp2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcapp2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfcapp2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCAPP2_H__AFC9C446_A781_428F_85AB_52A683D949AB__INCLUDED_)
