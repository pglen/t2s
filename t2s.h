// t2s.h : main header file for the T2S application
//

#if !defined(AFX_T2S_H__9E01D525_1861_489F_9786_AAD5D76D19BC__INCLUDED_)
#define AFX_T2S_H__9E01D525_1861_489F_9786_AAD5D76D19BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CT2sApp:
// See t2s.cpp for the implementation of this class
//

class CT2sApp : public CWinApp
{
public:
	CT2sApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT2sApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CT2sApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T2S_H__9E01D525_1861_489F_9786_AAD5D76D19BC__INCLUDED_)
