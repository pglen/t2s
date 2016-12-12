// t2sDlg.h : header file
//

#if !defined(AFX_T2SDLG_H__12597E76_0F97_4208_ADCE_0DA1C527A278__INCLUDED_)
#define AFX_T2SDLG_H__12597E76_0F97_4208_ADCE_0DA1C527A278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextProg.h"

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override something,
//but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

// This macro assumes a lot about the context, just for simplification

#define RES_BUT(but, var_x, var_y)						\
	GetDlgItem(but)->GetWindowPlacement(&wp);			\
	var_x = rc.right - wp.rcNormalPosition.left;		\
	var_y = rc.bottom - wp.rcNormalPosition.top;	

// This macro assumes a lot about the context, just for simplification

#define MOVE_BUT(but, var_x, var_y)						\
	GetDlgItem(but)->SetWindowPos						\
		(NULL, rc.right - var_x,  rc.bottom - var_y,	\
			0, 0, SWP_NOZORDER | SWP_NOSIZE);	

/////////////////////////////////////////////////////////////////////////////
// CT2sDlg dialog

class CT2sDlg : public CDialog

{	
	HWND oldclip;

// Construction
public:
	void Resize();
	CT2sDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CT2sDlg)
	enum { IDD = IDD_T2S_DIALOG };
	CTextProg	m_prog;
	CEdit	m_edit;
	CString	m_str;
	BOOL	m_clip;
	BOOL	m_top;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT2sDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	int		ok_x, ok_y, can_x, can_y;
	int		b1_x, b1_y, b2_x, b2_y, b4_x, b4_y, b5_x, b5_y;
	int		b6_x, b6_y, c1_x, c1_y, c2_x, c2_y;
	
	int		ed1_left, ed1_top, ed1_gapx, ed1_gapy;

	int sizing;

	// Generated message map functions
	//{{AFX_MSG(CT2sDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnDestroy();
	afx_msg void OnButton2();
	afx_msg void OnDrawClipboard();
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnCheck2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T2SDLG_H__12597E76_0F97_4208_ADCE_0DA1C527A278__INCLUDED_)
