// mfcapp2Dlg.h : header file
//
#include <SndObj/AudioDefs.h>

#if !defined(AFX_MFCAPP2DLG_H__2B628552_2472_4EE3_8EEC_F38E798FDFF2__INCLUDED_)
#define AFX_MFCAPP2DLG_H__2B628552_2472_4EE3_8EEC_F38E798FDFF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfcapp2Dlg dialog

extern "C" {
void SndThreadProc(
  LPVOID lpParameter   // thread data
  );

}
class CMfcapp2Dlg : public CDialog
{
// Construction
public:
	int cnot;
	void FreeSndObj();
	int InitSndObj();
	CMfcapp2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfcapp2Dlg)
	enum { IDD = IDD_MFCAPP2_DIALOG };
	CButton	m_adsynbut;
	CEdit	m_pviewctl;
	CEdit	m_tviewctl;
	CButton	m_exitctl;
	CSliderCtrl	m_tscalectl;
	CButton	m_processctl;
	CSliderCtrl	m_pitchctl;
	CEdit	m_filenamectl;
	CButton	m_browsectl;
	CString	m_filename;
	int		m_pitch;
	int		m_tscale;
	int		m_adsynon;
	int		m_dftctl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcapp2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMfcapp2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnReleasedcapturePitch(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnProcess();
	afx_msg void OnReleasedcaptureTscale(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeFilename();
	afx_msg void OnAdsyn1();
	afx_msg void OnResyn();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

char* infile;	
float stratio;  // time-stretch ratio
float pitch;
float thresh ;  // analysis threshold
int intracks;  // analysis max number of tracks
int outracks ;  // synthesis
int fftsize;     // FFT analysis size
int decimation;      // analysis hopsize
int interpolation ; // synthesis hopsize  
float scale ;   // scaling factor

SndRTIO *output;
SinSyn *synth;
SinAnal *sinus;
PVA *ifgram;
SndIn  *insound;
SndWave *input;
Table   *window;
Table   *table;
SndThread *thread;

bool endt;
HANDLE thnd;
BOOL processing;
DWORD threadid;                         

friend void SndThreadProc(
  LPVOID lpParameter   // thread data
  );

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCAPP2DLG_H__2B628552_2472_4EE3_8EEC_F38E798FDFF2__INCLUDED_)
