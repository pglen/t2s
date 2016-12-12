#if !defined(AFX_TEXTPROG_H__736D85C8_870F_4D9F_9E5B_DA2D5CEE0E0F__INCLUDED_)
#define AFX_TEXTPROG_H__736D85C8_870F_4D9F_9E5B_DA2D5CEE0E0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextProg.h : header file
//

#include <afxmt.h>


/////////////////////////////////////////////////////////////////////////////
// CTextProg window

class CTextProg : public CStatic
{
// Construction
public:
	CTextProg();
	virtual ~CTextProg();

// Attributes
public:

// Operations
public:

	CMutex mx;	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextProg)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL


	// Implementation

public:
	void ReScan();

	void HighLite(int start, int end);
	void SetText(CString *pstr);
	void SetText(const char *pstr);

protected:

	LOGFONT		m_lf;
	CFont		m_font;
	
	CStringArray linearr;
	CStringArray showarr;
	

	CDWordArray	xarr, yarr, offs, offs2;

	int startx, endx;

	// Generated message map functions

	//{{AFX_MSG(CTextProg)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPROG_H__736D85C8_870F_4D9F_9E5B_DA2D5CEE0E0F__INCLUDED_)
