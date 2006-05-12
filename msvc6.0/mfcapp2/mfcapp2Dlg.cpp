// mfcapp2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include <process.h>
#include "mfcapp2.h"
#include "mfcapp2Dlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void  SndThreadProc(
  LPVOID lpParameter   // thread data
  ){

CMfcapp2Dlg *p = (CMfcapp2Dlg *) lpParameter;

SndIO *in, *out;
SndObj *obj[4];
obj[0] = p->insound;
obj[1] = p->ifgram;
obj[2] = p->sinus;
obj[3] = p->synth;
in = p->input;
out = p->output;
bool *endt = &p->endt;
float* stratio = &(p->stratio), str;

	float rem = 0.f;
	int cnt = (int) *stratio;
	int icnt  = 1;
      
	while(!((SndFIO *)in)->Eof()){
    if(*endt) return;
	while(icnt--){
    in->Read();
	for(int n=0;  n < 3; n++)  obj[n]->DoProcess();
	}
	while(cnt--){
	obj[3]->DoProcess();
    out->Write();
	}
	if(*stratio < 1 && *stratio > 0 ){
	str = 1.f/ *stratio;
	icnt = (int) str;
	rem += str - icnt;
    if(rem >= 1){
		icnt++;
		rem = 0.f;
	}
	cnt = 1;
	}
	else {
	cnt = (int) *stratio;
	rem += *stratio - cnt;
    if(rem >= 1){
		cnt++;
		rem = 0.f;
	}
	icnt = 1;
	}
	}
   ((SndWave *)in)->SetPos(0L);
	p->m_filenamectl.EnableWindow();
	p->m_browsectl.EnableWindow();
    p->processing = !p->processing;
	p->m_processctl.SetWindowText("play");
	p->GetDlgItem(IDC_RADIO1)->EnableWindow();
	p->GetDlgItem(IDC_RADIO2)->EnableWindow();
	p->GetDlgItem(IDC_RADIO3)->EnableWindow();
	p->GetDlgItem(IDC_RADIO4)->EnableWindow();
	p->endt = true; 
}



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
// CMfcapp2Dlg dialog

CMfcapp2Dlg::CMfcapp2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcapp2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMfcapp2Dlg)
	m_filename = _T("");
	m_pitch = (1000-25)/100;
	m_tscale = (200-25)/100;
	m_adsynon = 0;
	m_dftctl = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
cnot = 0;
stratio  = 1.5f;   
pitch  = 1.f;
thresh = 0.003f;
intracks = 500;  
outracks = 500;  
fftsize =  2048;     
decimation =  fftsize/4;    
interpolation = fftsize/4; 
scale = 2.f;   
processing = FALSE;
synth = NULL;
infile = NULL;
  synth = NULL;
  ifgram = NULL;
  sinus = NULL;
  insound = NULL;
  input = NULL;
  output = NULL;
	table = new HarmTable(10000, 1, 1, 0.25);    // cosine wave
		window = new HammingTable(fftsize, 0.5); // hanning window
	m_tscalectl.SetRange(25,1000);
	m_tviewctl.SetWindowText("1.00");
	m_pitchctl.SetRange(25,200);
	m_pviewctl.SetWindowText("1.00");

}
void CMfcapp2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcapp2Dlg)
	DDX_Control(pDX, IDC_RADIO1, m_adsynbut);
	DDX_Control(pDX, IDC_PVIEW, m_pviewctl);
	DDX_Control(pDX, IDC_TVIEW, m_tviewctl);
	DDX_Control(pDX, IDOK, m_exitctl);
	DDX_Control(pDX, IDC_TSCALE, m_tscalectl);
	DDX_Control(pDX, IDC_PROCESS, m_processctl);
	DDX_Control(pDX, IDC_PITCH, m_pitchctl);
	DDX_Control(pDX, IDC_FILENAME, m_filenamectl);
	DDX_Control(pDX, IDC_BROWSE, m_browsectl);
	DDX_Text(pDX, IDC_FILENAME, m_filename);
	DDX_Slider(pDX, IDC_PITCH, m_pitch);
	DDX_Slider(pDX, IDC_TSCALE, m_tscale);
	DDX_Radio(pDX, IDC_RADIO1, m_adsynon);
	DDX_Radio(pDX, IDC_RADIO3, m_dftctl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfcapp2Dlg, CDialog)
	//{{AFX_MSG_MAP(CMfcapp2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PITCH, OnReleasedcapturePitch)
	ON_BN_CLICKED(IDC_PROCESS, OnProcess)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_TSCALE, OnReleasedcaptureTscale)
	ON_EN_CHANGE(IDC_FILENAME, OnChangeFilename)
	ON_BN_CLICKED(IDC_RADIO1, OnAdsyn1)
	ON_BN_CLICKED(IDC_RADIO2, OnResyn)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcapp2Dlg message handlers

BOOL CMfcapp2Dlg::OnInitDialog()
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
	m_tscalectl.SetRange(25,1000);
	m_tviewctl.SetWindowText("1.00");
	m_pitchctl.SetRange(25,200);
	m_pviewctl.SetWindowText("1.00");

		m_pitchctl.SetPos(100);
			m_tscalectl.SetPos(100);
						m_pitch = 100.f;
			m_tscale= 100.f;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMfcapp2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcapp2Dlg::OnPaint() 
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
HCURSOR CMfcapp2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMfcapp2Dlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
		CFileDialog  Browse(TRUE, // TRUE for FileOpen, FALSE for FileSaveAs
	    "wav",
		"*.wav",
		OFN_FILEMUSTEXIST,
		"*.wav",
		this); 
	Browse.m_ofn.lpstrTitle = "input soundfile";

	if( Browse.DoModal() == IDOK){
    m_filename = Browse.GetPathName();
	OnInitDialog();

	}

	m_tviewctl.SetWindowText("1.00");
	m_pviewctl.SetWindowText("1.00");
			m_pitchctl.SetPos(100);
			m_tscalectl.SetPos(100);
			pitch = 1.f;
			stratio =1.f;
			m_pitch = 100.f;
			m_tscale= 100.f;
	if(infile != NULL) delete[] infile;
	infile = new char[100];
	strcpy(infile, (LPCTSTR) m_filename);
	if(input != NULL){
		delete input;
		FreeSndObj();
	}
	input = new SndWave(infile, READ,1,16,0,0.f,decimation);
	InitSndObj();
}

void CMfcapp2Dlg::OnReleasedcapturePitch(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_pitch = m_pitchctl.GetPos();
	pitch = (m_pitch/100.f);
    char value[10];
	sprintf(value, "%2.2f",pitch);
	m_pviewctl.SetWindowText(value);
    if(synth != NULL)
	synth->Set("pitch", pitch);
	*pResult = 0;
}

void CMfcapp2Dlg::OnProcess() 
{
	// TODO: Add your control notification handler code here
		if(m_filename == "") {
		AfxMessageBox("please select an input file");
		return ;
	}
		else {
	if(!processing){
	if(output != NULL) delete output; 
	output = new SndRTIO(1,SND_OUTPUT,2048,4,SHORTSAM,0,interpolation);
	output->SetOutput(1, synth);
	endt = false;
     _beginthread(SndThreadProc, NULL, (void *) this);	
	m_processctl.SetWindowText("stop");
	m_filenamectl.EnableWindow(FALSE);
	m_browsectl.EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
    processing = !processing;

	}
	else {
	endt = true;
    Sleep(500);
	m_filenamectl.EnableWindow();
	m_browsectl.EnableWindow();
    processing = !processing;
	GetDlgItem(IDC_RADIO1)->EnableWindow();
	GetDlgItem(IDC_RADIO2)->EnableWindow();
	GetDlgItem(IDC_RADIO3)->EnableWindow();
	GetDlgItem(IDC_RADIO4)->EnableWindow();
	m_processctl.SetWindowText("play");
	delete output;
	output = NULL;
	}
		}
		}


void CMfcapp2Dlg::OnReleasedcaptureTscale(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_tscale = m_tscalectl.GetPos();
	stratio = (m_tscale/100.f);
	char value[10];
	sprintf(value, "%2.2f",stratio);
	m_tviewctl.SetWindowText(value);
	*pResult = 0;
}

void CMfcapp2Dlg::OnChangeFilename() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	   	GetDlgItemText(IDC_FILENAME, m_filename);
			if(infile != NULL) delete[] infile;
	infile = new char[100];
	strcpy(infile, (LPCTSTR) m_filename);
	if(input != NULL){
		delete input;
		FreeSndObj();
	}
	input = new SndWave(infile, READ,1,16,0,0.f,decimation);
	InitSndObj();
}

int CMfcapp2Dlg::InitSndObj()
{

	interpolation = decimation;
	// input sound
	insound = new SndIn (input, 1, decimation);
	// IFD analysis
	ifgram = new IFGram(window,insound,1.f,fftsize,decimation);
	// Sinusoidal analysis

	sinus =  new SinAnal(ifgram,thresh,intracks, 1, 1);

	// Sinusoidal resynthesis
	synth = (m_adsynon != 0 ? 
		new ReSyn(sinus,outracks,table,pitch,scale, stratio,interpolation) :
	    new AdSyn(sinus,outracks,table,pitch,scale,interpolation));
	return 1;
}

void CMfcapp2Dlg::FreeSndObj()
{
  delete synth;
  //delete sinus;
  //delete ifgram;
  delete insound;
}

void CMfcapp2Dlg::OnAdsyn1() 
{
	// TODO: Add your control notification handler code here
	if  (IsDlgButtonChecked (IDC_RADIO1)){
		m_adsynon = 0;
		FreeSndObj();
	    InitSndObj();
	}
}

void CMfcapp2Dlg::OnResyn() 
{
	// TODO: Add your control notification handler code here
	if  (IsDlgButtonChecked (IDC_RADIO2)){
			m_adsynon = 1;
			FreeSndObj();
	        InitSndObj();
	}
	
}

void CMfcapp2Dlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	if  (IsDlgButtonChecked (IDC_RADIO3)){
				fftsize = 1024;
    decimation =  256;    
    interpolation = 256; 
    delete window;
	window = new HammingTable(fftsize, 0.5); // hanning window
	if(input != NULL)
	delete input;
	FreeSndObj();
	input = new SndWave(infile, READ,1,16,0,0.f,decimation);
	InitSndObj();
				}
}


void CMfcapp2Dlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	if  (IsDlgButtonChecked (IDC_RADIO4)){
	fftsize = 2048;
	decimation =  512;    
    interpolation = 512; 
    delete window;
	window = new HammingTable(fftsize, 0.5); // hanning window
	delete input;
	FreeSndObj();
	input = new SndWave(infile, READ,1,16,0,0.f,decimation);
	InitSndObj();
				}
}
