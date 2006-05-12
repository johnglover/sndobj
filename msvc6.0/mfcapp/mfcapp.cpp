// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information
// mfcapp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "mfcapp.h"
#include "mfcappDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcappApp

BEGIN_MESSAGE_MAP(CMfcappApp, CWinApp)

ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcappApp construction

CMfcappApp::CMfcappApp()
{  }

/////////////////////////////////////////////////////////////////////////////
// The one and only CMfcappApp object

CMfcappApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMfcappApp initialization

BOOL CMfcappApp::InitInstance()
{

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMfcappDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{ }
	else if (nResponse == IDCANCEL)
	{ }

	return FALSE;
}
