// Copyright (c)Victor Lazzarini, 1997-2004
// See License.txt for a disclaimer of all warranties
// and licensing information

// mfcappDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcapp.h"
#include "mfcappDlg.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:


	CAboutDlg();

// Dialog Data  
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcappDlg dialog

CMfcappDlg::CMfcappDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcappDlg::IDD, pParent)
{
    // SndObj Library Initialisation
	buffersize = 256;
	m_alloc = false;
    InitSndObj();
    
	//{{AFX_DATA_INIT(CMfcappDlg)
	m_proc = FALSE;
	m_smamp = 0;
	m_smfreq = 0;
	m_latency = 0;
	m_lnk = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMfcappDlg::~CMfcappDlg(){

FreeSndObj();

}

void CMfcappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcappDlg)
	DDX_Control(pDX, IDOK, m_exit);
	DDX_Control(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_scroll2);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scroll1);
	DDX_Check(pDX, IDC_CHECK1, m_proc);
	DDX_Scroll(pDX, IDC_SCROLLBAR1, m_smamp);
	DDX_Scroll(pDX, IDC_SCROLLBAR2, m_smfreq);
	DDX_Radio(pDX, IDC_RADIO1, m_latency);
	DDX_Check(pDX, IDC_CHECK2, m_lnk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfcappDlg, CDialog)
	//{{AFX_MSG_MAP(CMfcappDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcappDlg message handlers

BOOL CMfcappDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		 
	 m_scroll1.SetScrollRange(0, 100);
	 m_scroll2.SetScrollRange(0, 100);
	 m_scroll1.SetScrollPos(50);
	 m_scroll2.SetScrollPos(50);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMfcappDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMfcappDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMfcappDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMfcappDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_proc =! m_proc;
	if(m_proc) {
		thread->ProcOn();
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
		m_exit.EnableWindow(FALSE);
	}
    else {
		thread->ProcOff();
		GetDlgItem(IDC_RADIO1)->EnableWindow();
		GetDlgItem(IDC_RADIO2)->EnableWindow();
        GetDlgItem(IDC_RADIO3)->EnableWindow();
		m_exit.EnableWindow();
	}
}


void CMfcappDlg::InitSndObj()
{
	if(!m_alloc){

window = new HammingTable(1024, 0.5);
input = new SndRTIO(2, SND_INPUT, buffersize);
insound1 = new SndIn(input, 1);
insound2 = new SndIn(input, 2);
spec1 = new PVA(window, insound1, 1.f);
spec2 = new PVA(window, insound2, 1.f);
morph = new PVMorph(0.5f, 0.5f, spec1, spec2);
synth = new PVS(window, morph);
output = new SndRTIO(1, SND_OUTPUT, buffersize);
output->SetOutput(1, synth);

thread = new SndThread;

thread->AddObj(insound1);
thread->AddObj(insound2);
thread->AddObj(spec1);
thread->AddObj(spec2);
thread->AddObj(morph);
thread->AddObj(synth);
thread->AddObj(input, SNDIO_IN);
thread->AddObj(output, SNDIO_OUT); // adds output to the out list

m_alloc = true;
	}
}



void CMfcappDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default    

	if(pScrollBar == &m_scroll1){
	switch(nSBCode){
	case SB_THUMBTRACK:
	m_smamp = nPos;
	morph->SetAmpMorph(m_smamp/100.f);
	default:
	pScrollBar->SetScrollPos(m_smamp);
    }
	if(m_lnk) {
		switch(nSBCode){
	case SB_THUMBTRACK:
	m_smfreq = nPos;
	morph->SetFreqMorph(m_smfreq/100.f);
	default:
	m_scroll2.SetScrollPos(m_smfreq);
	}

	}
    }
	else {
    switch(nSBCode){
	case SB_THUMBTRACK:
	m_smfreq = nPos;
	morph->SetFreqMorph(m_smfreq/100.f);
	default:
	pScrollBar->SetScrollPos(m_smfreq);
    }
    if(m_lnk){
    switch(nSBCode){
	case SB_THUMBTRACK:
	m_smamp = nPos;
	morph->SetAmpMorph(m_smamp/100.f);
	default:
	m_scroll1.SetScrollPos(m_smamp);
	}
	}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

}

void CMfcappDlg::FreeSndObj()
{
	if(m_alloc){
try{
delete thread;
delete output;
delete morph;
delete spec1;
delete spec2;
delete insound1;
delete insound2;
delete input;
delete window;
delete synth; 
}
catch (...){ };

m_alloc = false;
	}
}

void CMfcappDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
		if  (IsDlgButtonChecked (IDC_RADIO1))
	{
	buffersize = 256;
     
	thread->DeleteObj(output, SNDIO_OUT);
	delete output;
    output = new SndRTIO(1, SND_OUTPUT, buffersize);
    output->SetOutput(1, synth);
	thread->AddObj(output, SNDIO_OUT);
	}

}

void CMfcappDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
			if  (IsDlgButtonChecked (IDC_RADIO2))
	{
	buffersize = 512;
	thread->DeleteObj(output, SNDIO_OUT);
	output->Write();
	delete output;

    output = new SndRTIO(1, SND_OUTPUT, buffersize);
    output->SetOutput(1, synth);
	thread->AddObj(output, SNDIO_OUT);
	}
	
	
}

void CMfcappDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
			if  (IsDlgButtonChecked (IDC_RADIO3))
	{
	buffersize = 1024;
  
    thread->DeleteObj(output, SNDIO_OUT);
	delete output;
    output = new SndRTIO(1, SND_OUTPUT, buffersize);
    output->SetOutput(1, synth);
	thread->AddObj(output, SNDIO_OUT);
   }	
  
}

void CMfcappDlg::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	m_lnk =! m_lnk;
}
