// granulatorDlg.h : header file
//

#if !defined(AFX_GRANULATORDLG_H__5A79BF08_369A_11D6_B211_00C04F8906D8__INCLUDED_)
#define AFX_GRANULATORDLG_H__5A79BF08_369A_11D6_B211_00C04F8906D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <SndObj/AudioDefs.h>
#include "ProgDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CGranulatorDlg dialog

class CGranulatorDlg : public CDialog
{
// Construction
public:
	~CGranulatorDlg();
	CGranulatorDlg(CWnd* pParent = NULL);	// standard constructor
    SyncGrain*  m_grain;
	SndWave*  m_input;
	SndTable* m_table;
	HammingTable* m_envtb;

    int    m_on;
	CWinThread* m_pthread;

    float m_amp;
	float m_dens;
	float m_grsize;
	float m_prate;
	float m_pitch;

	CProgressDlg m_progrbar;

// Dialog Data
	//{{AFX_DATA(CGranulatorDlg)
	enum { IDD = IDD_GRANULATOR_DIALOG };
	CEdit	m_foutedit;
	CButton	m_buttoutfile;
	CButton	m_ok;
	CButton	m_filebutton;
	CSliderCtrl	m_pratectl;
	CEdit	m_pratedit;
	CSliderCtrl	m_pitchctl;
	CEdit	m_pitchedit;
	CSliderCtrl	m_grsizectl;
	CEdit	m_grsizedit;
	CEdit	m_fedit;
	CSliderCtrl	m_densityctl;
	CEdit	m_densedit;
	CEdit	m_ampedit;
	CSliderCtrl	m_ampctl;
	CButton	m_processbutton;
	CString	m_fname;
	CString	m_amptxt;
	CString	m_denstxt;
	CString	m_grsizetxt;
	CString	m_pitchtxt;
	CString	m_pratetxt;
	BOOL	m_fileout;
	CString	m_outputfilename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGranulatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGranulatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileButton();
	afx_msg void OnChangeFile();
	afx_msg void OnProcess();
	afx_msg void OnReleasedcaptureAmpslider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeAmp();
	afx_msg void OnReleasedcaptureDensityslider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeDensity();
	afx_msg void OnChangeGrsize();
	afx_msg void OnReleasedcaptureGrsizeslider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangePitch();
	afx_msg void OnReleasedcapturePitchslider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangePrate();
	afx_msg void OnReleasedcapturePrateslider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck1();
	afx_msg void OnChangeFileout();
	afx_msg void OnButtoutfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRANULATORDLG_H__5A79BF08_369A_11D6_B211_00C04F8906D8__INCLUDED_)
