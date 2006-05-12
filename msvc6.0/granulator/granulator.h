// granulator.h : main header file for the GRANULATOR application
//

#if !defined(AFX_GRANULATOR_H__5A79BF06_369A_11D6_B211_00C04F8906D8__INCLUDED_)
#define AFX_GRANULATOR_H__5A79BF06_369A_11D6_B211_00C04F8906D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGranulatorApp:
// See granulator.cpp for the implementation of this class
//

class CGranulatorApp : public CWinApp
{
public:
	CGranulatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGranulatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGranulatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRANULATOR_H__5A79BF06_369A_11D6_B211_00C04F8906D8__INCLUDED_)
