// t2sDlg.cpp : implementation file
//

#include "stdafx.h"
#include "t2s.h"
#include "t2sDlg.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Speak.h"

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


CSpeak	sp;

/////////////////////////////////////////////////////////////////////////////
// CT2sDlg dialog

CT2sDlg::CT2sDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CT2sDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CT2sDlg)
	m_str = _T("");
	m_clip = FALSE;
	m_top = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	oldclip = 0;
	sizing = 0;
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CT2sDlg)
	DDX_Control(pDX, IDC_PROG, m_prog);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Check(pDX, IDC_CHECK1, m_clip);
	DDX_Check(pDX, IDC_CHECK2, m_top);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CT2sDlg, CDialog)
	//{{AFX_MSG_MAP(CT2sDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_DRAWCLIPBOARD()
	ON_WM_CHANGECBCHAIN()
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT2sDlg message handlers

BOOL CT2sDlg::OnInitDialog()
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
	
	SetClipboardViewer();

	m_str = "Hello World";
	m_clip = true;
	sp.postto = m_hWnd;
	m_prog.SetText(&m_str);

	UpdateData(false);
	
	RECT rc; GetClientRect(&rc);

		// Geometry for buttons

	//////////////////////////////////////////////////////////////////////////
	WINDOWPLACEMENT wp;

	GetDlgItem(IDOK)->GetWindowPlacement(&wp);
	ok_x = rc.right - wp.rcNormalPosition.left;	
	ok_y = rc.bottom - wp.rcNormalPosition.top;	

	GetDlgItem(IDCANCEL)->GetWindowPlacement(&wp);
	can_x = rc.right - wp.rcNormalPosition.left;
	can_y = rc.bottom - wp.rcNormalPosition.top;	

	RES_BUT(IDC_BUTTON1, b1_x, b1_y);
	RES_BUT(IDC_BUTTON2, b2_x, b2_y);
	RES_BUT(IDC_BUTTON4, b4_x, b4_y);
	RES_BUT(IDC_BUTTON5, b5_x, b5_y);
	RES_BUT(IDC_BUTTON6, b6_x, b6_y);

	RES_BUT(IDC_CHECK1, c1_x, c1_y);
	RES_BUT(IDC_CHECK2, c2_x, c2_y);

	GetDlgItem(IDC_PROG)->GetWindowPlacement(&wp);
	ed1_left	= wp.rcNormalPosition.left;	
	ed1_top		= wp.rcNormalPosition.top;	
	ed1_gapx    = rc.right  - wp.rcNormalPosition.right;	
	ed1_gapy    = rc.bottom - wp.rcNormalPosition.bottom;	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CT2sDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CT2sDlg::OnPaint() 
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
		if(!sizing)
			CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR CT2sDlg::OnQueryDragIcon()

{
	return (HCURSOR) m_hIcon;
}

void CT2sDlg::OnButton1() 

{
	//UpdateData();
	
	//m_prog.text = m_str;
	//m_prog.Invalidate();
	
	sp.Speak(m_str);

	//AfxMessageBox(m_str);	

}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnDestroy() 

{
	CDialog::OnDestroy();	
	ChangeClipboardChain(oldclip);
}

//////////////////////////////////////////////////////////////////////////
// Kill thread

void CT2sDlg::OnButton2() 

{
	//TRACE("CT2sDlg::OnButton2\r\n");
	sp.Stop();	
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnDrawClipboard() 

{
	CDialog::OnDrawClipboard();
	
	//TRACE("CT2sDlg::OnDrawClipboard\r\n");

	// See if text changed
	UpdateData();

	if(m_clip)
		{
		VERIFY(OpenClipboard());

		HANDLE hh = GetClipboardData(CF_TEXT);

		if(hh)
			{
			int len = GlobalSize(hh);

			if(len)
				{
				len = min(len, 2000);

				void *ptr = GlobalLock(hh); ASSERT(ptr);
				
				// CString 			
				char *sptr = m_str.GetBuffer(len); ASSERT(sptr);
				memcpy(sptr, ptr, len);
				m_str.ReleaseBuffer();
				
				//m_str =  (char*) ptr;

				//TRACE("%s\r\n", m_str);

				UpdateData(false);
				
				GlobalUnlock(hh);
			
				m_prog.SetText(&m_str);
			
				SetTimer(2, 100, NULL);				
				}
			}
		VERIFY(CloseClipboard());
		}

	if(oldclip)
		{
		::SendMessage(oldclip, WM_DRAWCLIPBOARD, 0, 0);
		}
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 

{
	CDialog::OnChangeCbChain(hWndRemove, hWndAfter);
	
	if(hWndRemove == oldclip)
		{
		oldclip = hWndAfter;
		}
	else
		{
		::SendMessage(oldclip, WM_CHANGECBCHAIN, (DWORD)hWndRemove, (DWORD)hWndAfter);
		}
}

void CT2sDlg::OnCheck2() 

{
	UpdateData();

	if(m_top)
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, 
					SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW   );	
	else
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, 
					SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW   );	

}

//////////////////////////////////////////////////////////////////////////

BOOL CT2sDlg::PreTranslateMessage(MSG* pMsg) 

{
	if(pMsg->message == WM_USER+1)
		{
		int len = LOWORD(pMsg->lParam), start = HIWORD(pMsg->lParam);

		//m_edit.SetFocus();

		// CEdit 
		if(pMsg->wParam == SPRS_IS_SPEAKING)
			{
			//P2N("Set sel %d %d\r\n", start, start + len + 1);
			//m_edit.SetSel(start, start + len + 1);

			m_prog.HighLite(start, start + len);
			}
		else
			{
			//P2N("Clear Sel\r\n");
			//m_edit.SetSel(0, -1);
			//m_edit.SetSel(-1, 0);
			m_prog.HighLite(-1, -1);
			}
		//m_edit.Invalidate();
		//m_edit.SetWindowText("eee");
		}


	return CDialog::PreTranslateMessage(pMsg);
}

void CT2sDlg::OnButton3() 
{
	sp.Prop();		
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnButton4() 

{
	VERIFY(OpenClipboard());

	HANDLE hh = GetClipboardData(CF_TEXT);

	if(hh)
		{
		int len = GlobalSize(hh);
		if(len)
			{
			void *ptr = GlobalLock(hh);

			len = min(len, 2000);

			m_prog.SetText((const char*)ptr);

			// CString 			
			char *sptr = m_str.GetBuffer(len); ASSERT(sptr);
			memcpy(sptr, ptr, len);
			m_str.ReleaseBuffer();
		
			//m_str = (const char*)ptr;

			GlobalUnlock(hh);
			}
		}

	VERIFY(CloseClipboard());	
}

void CT2sDlg::OnButton5() 
{
	sp.Skip(-1);	
}

void CT2sDlg::OnButton6() 

{
	sp.Skip(1);	
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnSize(UINT nType, int cx, int cy) 

{
	//CDialog::OnSize(nType, cx, cy);
	
	//P2N("CT2sDlg::OnSize cx=%d cy=%d\r\n",  cx, cy);	

	CButton  *ok = (CButton*)GetDlgItem(IDOK);
		
	if(ok)
		if(IsWindow(ok->m_hWnd))
			Resize();
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::Resize()

{
	RECT rc; GetClientRect(&rc);

	//sizing = true;

	// Right aligned
	GetDlgItem(IDOK)->SetWindowPos(NULL, rc.right - ok_x,  rc.bottom - ok_y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	MOVE_BUT(IDC_BUTTON1, b1_x, b1_y);
	MOVE_BUT(IDC_BUTTON2, b2_x, b2_y);
	MOVE_BUT(IDC_BUTTON4, b4_x, b4_y);
	MOVE_BUT(IDC_BUTTON5, b5_x, b5_y);
	MOVE_BUT(IDC_BUTTON6, b6_x, b6_y);

	MOVE_BUT(IDC_CHECK1, c1_x, c1_y);
	MOVE_BUT(IDC_CHECK2, c2_x, c2_y);

	// Fill it up
	GetDlgItem(IDC_PROG)->SetWindowPos(NULL, ed1_left, ed1_top, 
								rc.right - ed1_gapx - ed1_left,  rc.bottom - ed1_gapy - ed1_top, SWP_NOZORDER);
	
	SetTimer(1, 300, NULL);
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnTimer(UINT nIDEvent) 

{
	if(nIDEvent == 1)
		{
		KillTimer(nIDEvent);
		//P2N("CT2sDlg::OnTimer -- Invalidate timer\r\n");

		sizing = false;
		Invalidate();	
		}	

	if(nIDEvent == 2)
		{
		KillTimer(nIDEvent);
	
		sp.Stop();
		sp.Speak(m_str);
		}

	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////

void CT2sDlg::OnSizing(UINT fwSide, LPRECT pRect) 

{
	CDialog::OnSizing(fwSide, pRect);
	
	//P2N("CT2sDlg::OnSizing\r\n");
	Invalidate();
}

void CT2sDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{

	lpMMI->ptMinTrackSize.x = 350;
	lpMMI->ptMinTrackSize.y = 90;

	CDialog::OnGetMinMaxInfo(lpMMI);
}
