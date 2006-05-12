// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

// mfcappDlg.h : header file
//

#if !defined(AFX_MFCAPPDLG_H__2CDE1D28_B146_11D7_B211_00C04F8906D8__INCLUDED_)
#define AFX_MFCAPPDLG_H__2CDE1D28_B146_11D7_B211_00C04F8906D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <SndObj/AudioDefs.h>

/////////////////////////////////////////////////////////////////////////////
// CMfcappDlg dialog

class CMfcappDlg : public CDialog
{
// Construction
public:
	float m_freqm;
	CMfcappDlg(CWnd* pParent = NULL);	// standard constructor
	~CMfcappDlg();
    int  buffersize;

	Table* window;
    SndThread* thread;
	SndIO* input;
    SndIO* output;
	SndIn* insound1;
	SndIn* insound2;
    PVA*  spec1;
	PVA*   spec2;
	PVS*  synth;
    PVMorph* morph;


 //Dialog Data
	//{{AFX_DATA(CMfcappDlg)
	enum { IDD = IDD_MFCAPP_DIALOG };
	CButton	m_exit;
	CButton	m_radio;
	CScrollBar	m_scroll2;
	CScrollBar	m_scroll1;
	BOOL	m_proc;
	int		m_smamp;
	int		m_smfreq;
	int		m_latency;
	BOOL	m_lnk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcappDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool m_alloc;
	void FreeSndObj();
	void InitSndObj();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMfcappDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCAPPDLG_H__2CDE1D28_B146_11D7_B211_00C04F8906D8__INCLUDED_)
