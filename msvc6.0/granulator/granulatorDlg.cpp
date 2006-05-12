// granulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "granulator.h"
#include "granulatorDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

inline float dBtoAmp(float amp){
	return (float) pow(10.0, amp/20.)*32767;
}

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
// CGranulatorDlg dialog

CGranulatorDlg::CGranulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGranulatorDlg::IDD, pParent)
{

	m_on = 0;
	//{{AFX_DATA_INIT(CGranulatorDlg)
	m_fname = _T("");
	m_amptxt = _T("");
	m_denstxt = _T("");
	m_grsizetxt = _T("");
	m_pitchtxt = _T("");
	m_pratetxt = _T("");
	m_fileout = FALSE;
	m_outputfilename = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_amp = -12.f;
    m_dens = 40.f;
	m_grsize = 0.05f;
	m_prate = 0.5f;
	m_pitch = 1.f;

    m_table  = 0;
	m_input  = 0;
	m_grain = 0;
	m_envtb = 0;

}

void CGranulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGranulatorDlg)
	DDX_Control(pDX, IDC_FILEOUT, m_foutedit);
	DDX_Control(pDX, IDC_BUTTOUTFILE, m_buttoutfile);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_BUTTON1, m_filebutton);
	DDX_Control(pDX, IDC_PRATESLIDER, m_pratectl);
	DDX_Control(pDX, IDC_PRATE, m_pratedit);
	DDX_Control(pDX, IDC_PITCHSLIDER, m_pitchctl);
	DDX_Control(pDX, IDC_PITCH, m_pitchedit);
	DDX_Control(pDX, IDC_GRSIZESLIDER, m_grsizectl);
	DDX_Control(pDX, IDC_GRSIZE, m_grsizedit);
	DDX_Control(pDX, IDC_EDIT1, m_fedit);
	DDX_Control(pDX, IDC_DENSITYSLIDER, m_densityctl);
	DDX_Control(pDX, IDC_DENSITY, m_densedit);
	DDX_Control(pDX, IDC_AMP, m_ampedit);
	DDX_Control(pDX, IDC_AMPSLIDER, m_ampctl);
	DDX_Control(pDX, IDC_PROCESS, m_processbutton);
	DDX_Text(pDX, IDC_EDIT1, m_fname);
	DDX_Text(pDX, IDC_AMP, m_amptxt);
	DDX_Text(pDX, IDC_DENSITY, m_denstxt);
	DDX_Text(pDX, IDC_GRSIZE, m_grsizetxt);
	DDX_Text(pDX, IDC_PITCH, m_pitchtxt);
	DDX_Text(pDX, IDC_PRATE, m_pratetxt);
	DDX_Check(pDX, IDC_CHECK1, m_fileout);
	DDX_Text(pDX, IDC_FILEOUT, m_outputfilename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGranulatorDlg, CDialog)
	//{{AFX_MSG_MAP(CGranulatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnFileButton)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeFile)
	ON_BN_CLICKED(IDC_PROCESS, OnProcess)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_AMPSLIDER, OnReleasedcaptureAmpslider)
	ON_EN_CHANGE(IDC_AMP, OnChangeAmp)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_DENSITYSLIDER, OnReleasedcaptureDensityslider)
	ON_EN_CHANGE(IDC_DENSITY, OnChangeDensity)
	ON_EN_CHANGE(IDC_GRSIZE, OnChangeGrsize)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_GRSIZESLIDER, OnReleasedcaptureGrsizeslider)
	ON_EN_CHANGE(IDC_PITCH, OnChangePitch)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PITCHSLIDER, OnReleasedcapturePitchslider)
	ON_EN_CHANGE(IDC_PRATE, OnChangePrate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PRATESLIDER, OnReleasedcapturePrateslider)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_CHANGE(IDC_FILEOUT, OnChangeFileout)
	ON_BN_CLICKED(IDC_BUTTOUTFILE, OnButtoutfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGranulatorDlg message handlers

BOOL CGranulatorDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	 int dec, sign;
	 m_ampctl.SetRange(-90, 0);
     m_ampctl.SetPos((int) m_amp);
     m_amptxt = _fcvt((double)m_amp, 1, &dec, &sign); 
	 m_amptxt.Insert(0, '-');
	 m_amptxt.Insert(m_amptxt.GetLength()-1, '.');
	 m_ampedit.SetWindowText((LPCTSTR) m_amptxt);
    
	 m_densityctl.SetRange(1, 1000);
     m_densityctl.SetPos((int)m_dens);
     m_denstxt = _fcvt((double)m_dens, 1, &dec, &sign); 
	 m_denstxt.Insert(m_denstxt.GetLength()-1, '.');
	 m_densedit.SetWindowText((LPCTSTR) m_denstxt);
	
	 m_pitchctl.SetRange(0, 1000);
     m_pitchctl.SetPos((int)(1000*m_pitch/2));
     m_pitchtxt = _fcvt((double)m_pitch, 3, &dec, &sign); 
	 m_pitchtxt.Insert(m_pitchtxt.GetLength()-3, '.');
	 m_pitchedit.SetWindowText((LPCTSTR) m_pitchtxt);
	
	 m_grsizectl.SetRange(5, 500);
     m_grsizectl.SetPos((int)(m_grsize*1000));
     m_grsizetxt = _fcvt((double)m_grsize*1000, 1, &dec, &sign); 
	 m_grsizetxt.Insert(m_grsizetxt.GetLength()-1, '.');
	 m_grsizedit.SetWindowText((LPCTSTR) m_grsizetxt);
	
     m_pratectl.SetRange(0, 1000);
	 m_pratectl.SetPos((int)(1000*m_prate/4.0));
     m_pratetxt = _fcvt((double)m_prate, 3, &dec, &sign); 
	 m_pratetxt.Insert(m_pratetxt.GetLength()-3, '.');
	 m_pratedit.SetWindowText((LPCTSTR) m_pratetxt);

	 m_buttoutfile.EnableWindow(m_fileout);
	 m_foutedit.EnableWindow(m_fileout);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGranulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGranulatorDlg::OnPaint() 
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
HCURSOR CGranulatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGranulatorDlg::OnFileButton() 
{

	CFileDialog  Browse(TRUE, // TRUE for FileOpen, FALSE for FileSaveAs
	    "wav",
		"*.wav",
		OFN_FILEMUSTEXIST,
		"*.wav",
		this); 
	Browse.m_ofn.lpstrTitle = "input soundfile";

	if( Browse.DoModal() == IDOK){


 m_progrbar.Create();
 m_fname = Browse.GetPathName();
  
 m_progrbar.StepIt();
 if(m_input)delete m_input;
 m_progrbar.StepIt();
 m_input = new SndWave(m_fname.GetBuffer(1), READ);	
 m_progrbar.StepIt();
 long size  = m_input->GetDataFrames();
 m_progrbar.StepIt();
 if(m_table) delete m_table;
 m_progrbar.StepIt();
 m_table =  new SndTable(size, m_input);
 m_progrbar.StepIt();
 if(!m_envtb)
	m_envtb = new HammingTable (1024, 0.54f); 
 m_progrbar.StepIt(); 
 if(m_grain) delete m_grain;
 m_progrbar.StepIt();
   m_grain =  new SyncGrain(m_table, m_envtb, m_dens, 
	                          dBtoAmp(m_amp)
							   ,m_pitch,m_grsize, 
							   m_prate);	
	
   m_progrbar.DestroyWindow();
	OnInitDialog();

	}


}

void CGranulatorDlg::OnChangeFile() 
{	
	GetDlgItemText(IDC_EDIT1, m_fname);
}


UINT Granulate(void* par){
  
  CGranulatorDlg* p = (CGranulatorDlg *) par;

  p->m_filebutton.EnableWindow(FALSE);
  p->m_foutedit.EnableWindow(FALSE);
  p->m_buttoutfile.EnableWindow(FALSE);
  p->m_ok.EnableWindow(FALSE);

  SndRTIO      *output = new SndRTIO(1, SND_OUTPUT, 1024); 
  SndWave      *foutput;
  
  output->SetOutput(1, p->m_grain);
  if(p->m_fileout){
	  foutput = new SndWave(p->m_outputfilename.GetBuffer(1));
      foutput->SetOutput(1, p->m_grain);
  }
  

   while(p->m_on){

   p->m_grain->DoProcess();
   output->Write();
   if(p->m_fileout) foutput->Write();
  }
 
  delete output;
  if(p->m_fileout) delete foutput;
  p->m_filebutton.EnableWindow();
  p->m_foutedit.EnableWindow(p->m_fileout);
  p->m_buttoutfile.EnableWindow(p->m_fileout);
  p->m_ok.EnableWindow();
  
  return 1;
  
}

void
CGranulatorDlg::OnProcess() 
{
 
  if(!strcmp((LPCTSTR) m_fname, "")){
   AfxMessageBox("No input file !!!", MB_OK, NULL);
  } 
  else{
  if(!m_on){
  m_on = 1;
  m_pthread = AfxBeginThread(Granulate, (LPVOID) this);
  }
  else {
   m_on = 0;
  }
  }
}

void CGranulatorDlg::OnReleasedcaptureAmpslider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_grain){
	 float amp = (float)m_ampctl.GetPos();
	 int dec, sign;
	 m_amptxt = _fcvt((double)amp, 1, &dec, &sign);
	 m_amptxt.Insert(0, '-');
	 m_amptxt.Insert(m_amptxt.GetLength()-1, '.');
	 m_ampedit.SetWindowText((LPCTSTR) m_amptxt);
	 for(int i = 0;  i < 50; i++) {
		m_grain->SetAmp(dBtoAmp(m_amp + ((amp-m_amp)*i/50)));
		Sleep(1);
		}
	 m_amp = amp;
	}
	 *pResult = 0;
}

void CGranulatorDlg::OnChangeAmp() 
{

	
}

void CGranulatorDlg::OnReleasedcaptureDensityslider(NMHDR* pNMHDR, LRESULT* pResult) 
{

		if(m_grain){
	 float dens = (float)m_densityctl.GetPos();
	 int dec, sign;
	 m_denstxt = _fcvt((double)dens, 1, &dec, &sign); 
	 m_denstxt.Insert(m_denstxt.GetLength()-1, '.');
	 m_densedit.SetWindowText((LPCTSTR) m_denstxt);
	 for(int i = 0;  i < 50; i++) {
		m_grain->SetFreq(m_dens + ((dens-m_dens)*i/50));
		Sleep(1);
		}
	 m_dens = dens;
		}
	 *pResult = 0;


	*pResult = 0;
}

void CGranulatorDlg::OnChangeDensity() 
{

	
}

void CGranulatorDlg::OnChangeGrsize() 
{
	

}

void CGranulatorDlg::OnReleasedcaptureGrsizeslider(NMHDR* pNMHDR, LRESULT* pResult) 
{
		if(m_grain){
	 float grsize = (float) m_grsizectl.GetPos();
	 int dec, sign;
	 m_grsizetxt = _fcvt((double)grsize, 1, &dec, &sign); 
	 m_grsizetxt.Insert(m_grsizetxt.GetLength()-1, '.');
	 m_grsizedit.SetWindowText((LPCTSTR) m_grsizetxt);
	 grsize = grsize/1000.f;
	 for(int i = 0;  i < 50; i++) {
		m_grain->SetGrainSize(m_grsize + ((grsize-m_grsize)*i/50));
		Sleep(1);
		}
	 m_grsize = grsize;
		}
	 *pResult = 0;
}

void CGranulatorDlg::OnChangePitch() 
{
	
}

void CGranulatorDlg::OnReleasedcapturePitchslider(NMHDR* pNMHDR, LRESULT* pResult) 
{
  if(m_grain){
     float pitch = ((float)m_pitchctl.GetPos()*2.f)/1000.f;
	 int dec, sign;
	 m_pitchtxt = _fcvt((double)pitch, 3, &dec, &sign); 
	 m_pitchtxt.Insert(m_pitchtxt.GetLength()-3, '.');
	 m_pitchedit.SetWindowText((LPCTSTR) m_pitchtxt);
	 for(int i = 0;  i < 50; i++) {
		m_grain->SetPitch(m_pitch + ((pitch-m_pitch)*i/50));
		Sleep(1);
		}
	 m_pitch = pitch;
  }
	 *pResult = 0;
}

void CGranulatorDlg::OnChangePrate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CGranulatorDlg::OnReleasedcapturePrateslider(NMHDR* pNMHDR, LRESULT* pResult) 
{
		if(m_grain){
     float prate = ((float)m_pratectl.GetPos()*4.f)/1000.f;
	 int dec, sign;
	 m_pratetxt = _fcvt((double)prate, 3, &dec, &sign); 
	 m_pratetxt.Insert(m_pratetxt.GetLength()-3, '.');
	 m_pratedit.SetWindowText((LPCTSTR) m_pratetxt);
	 for(int i = 0;  i < 50; i++) {
		m_grain->SetPointerRate(m_prate + ((prate-m_prate)*i/50));
		Sleep(1);
		}
	 m_prate = prate;
		}
	 *pResult = 0;
}

CGranulatorDlg::~CGranulatorDlg()
{
 if(m_grain) delete m_grain;
 if(m_input) delete m_input;
 if(m_table) delete m_table;
 if(m_envtb) delete m_envtb;
}

void CGranulatorDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_fileout = !m_fileout;
	m_buttoutfile.EnableWindow(m_fileout);
	m_foutedit.EnableWindow(m_fileout);
	
}

void CGranulatorDlg::OnChangeFileout() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

    
   	GetDlgItemText(IDC_FILEOUT, m_outputfilename);
	
}

void CGranulatorDlg::OnButtoutfile() 
{
	// TODO: Add your control notification handler code here
		CFileDialog  Browse(TRUE, // TRUE for FileOpen, FALSE for FileSaveAs
	    "wav",
		"*.wav",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"*.wav",
		this); 
	Browse.m_ofn.lpstrTitle = "output soundfile";

	if( Browse.DoModal() == IDOK){

    m_outputfilename = Browse.GetPathName();
 
	}
	
}
