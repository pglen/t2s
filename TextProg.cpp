// TextProg.cpp : implementation file
//

#include "stdafx.h"
#include "t2s.h"
#include "TextProg.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextProg

CTextProg::CTextProg()
{

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf);
	m_lf.lfHeight = 24;

	m_font.CreateFontIndirect(&m_lf);
	
	startx = endx = -1;
}

CTextProg::~CTextProg()
{
}


BEGIN_MESSAGE_MAP(CTextProg, CStatic)
	//{{AFX_MSG_MAP(CTextProg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// Parse into an array by spaces

void	ParseCRLF(CString *pstr, CStringArray *strarr, CDWordArray *offs)

{
	int rescnt = 0, create = true, len = pstr->GetLength();

	for(int loop = 0; loop < len; loop++)
		{
		char cc2 = 0, cc = pstr->GetAt(loop);

		if(loop + 1 < len)
			cc2 = pstr->GetAt(loop + 1);

		if(cc == '\r' && cc2 == '\n')
			{
			create = true;
			loop++;
			}
		else
			{
			if(create)
				{
				// New entry
				strarr->Add(""); create = false;
				offs->Add(loop);
				}
			// Append to last
			CString &str = strarr->ElementAt(strarr->GetUpperBound());
			str += cc;
			}
		}	
}

//////////////////////////////////////////////////////////////////////////
// Parse into an array by spaces

void	ParseSpaces(CString *pstr, CStringArray *strarr, CDWordArray *offs)

{	
	int rescnt = 0, create = true, len = pstr->GetLength();

	for(int loop = 0; loop < len; loop++)
		{
		char cc = pstr->GetAt(loop);

		if(cc == ' ')
			{
			create = true;
			}
		else
			{
			if(create)
				{
				// New entry
				strarr->Add(""); create = false;
				offs->Add(loop);
				}
			// Append to last
			CString &str = strarr->ElementAt(strarr->GetUpperBound());
			str += cc;
			}
		}	
}

/////////////////////////////////////////////////////////////////////////////
// CTextProg message handlers

void CTextProg::OnPaint() 

{
	CPaintDC dc(this); // device context for painting
		
	//P2N("CTextProg::OnPaint");

	RECT	rc; GetClientRect(&rc);
	rc.left += 4;	rc.right -= 4;

	CFont* oldFont = dc.SelectObject(&m_font);

	dc.FillSolidRect(&rc, GetSysColor(COLOR_3DFACE));

	//dc.SetBkMode(TRANSPARENT);	
	CSize ss2 = dc.GetTextExtent(" ", 1);

	int beg = 0, sub = 0;
	//int alen = showarr.GetSize();

	mx.Lock();

	// Determine if scrolling is needed		
	if(startx >= 0)
		{
		for(int loop = 0; loop < showarr.GetSize(); loop++)
			{
			int ofs = offs.GetAt(loop);
			
			//P2N("ofs=%d startx = %d endx=%d\r\n", ofs, startx, endx);
			// The highlite point
			if(ofs >= startx && ofs <= endx)
				{	
				int yyy = yarr.GetAt(loop);
				if(yyy + ss2.cy > rc.bottom)
					{
					//P2N("Scroll \r\n");				
						
					// Go back some ...
					for(int loop2 = loop; loop2 >= 0; loop2--)
						{
						int yyyy = yarr.GetAt(loop2);

						//P2N("yyyy=%d yyy=%d\r\n", yyyy, yyy);
			
						if( (yyy - yyyy) >= (rc.bottom / 2 ))
							{
							int loop3 = 0;
							// Find the beginning of the line
							for(loop3 = loop2; loop3 >= 0; loop3--)
								{
								int yyyy2 = yarr.GetAt(loop3);
								if(yyyy2 != yyyy)
									break;
								}
							beg = loop3;
							sub = yyyy;
							break;
							}
						}
					}
				break;
				}
			}
		}

	// Soft protect
	beg = max(beg, 0);

	//P2N("beg=%d sub=%d\r\n", beg, sub);

	for(int loop3 = beg; loop3 < showarr.GetSize(); loop3++)
		{
		CString val = showarr.GetAt(loop3);
			
		int xx = xarr.GetAt(loop3);
		int yy = yarr.GetAt(loop3) - sub;
		int ofs = offs.GetAt(loop3);
		
		if(ofs >= startx && ofs <= endx)
			dc.SetBkColor(	RGB(100,100,100));
		else
			dc.SetBkColor(	GetSysColor(COLOR_3DFACE));
		
		if(yy + ss2.cy - sub > rc.bottom)
			break;

 		//dc.ExtTextOut(xx, yy, ETO_OPAQUE, NULL, val, NULL);
		dc.ExtTextOut(xx, yy, 0, NULL, val, NULL);		
		}
	
	mx.Unlock();

	dc.SelectObject(oldFont);

	// Do not call CStatic::OnPaint() for painting messages
}

void CTextProg::PreSubclassWindow() 

{
	ModifyStyle(0, WS_CLIPCHILDREN | SS_NOTIFY);
	//ModifyStyleEx(WS_EX_STATICEDGE, 0, SWP_DRAWFRAME);
	
	CStatic::PreSubclassWindow();
}

//////////////////////////////////////////////////////////////////////////

void CTextProg::SetText(const char *pstr)

{
	CString str(pstr);
	SetText(&str);
}

void CTextProg::SetText(CString *pstr)

{	
	// Fresh Start
	linearr.RemoveAll();
	offs2.RemoveAll();

	ParseCRLF(pstr, &linearr, &offs2);
	
	ReScan();
	Invalidate();	
}

void CTextProg::HighLite(int start, int end)

{
	//P2N("CTextProg::HighLite(int start=%d, int end=%d)\r\n", start, end);

	startx = start; endx = end;
	Invalidate();
}

void CTextProg::ReScan()

{
	CPaintDC dc(this); // device context for painting

	RECT	rc; GetClientRect(&rc);
	rc.left += 4;	rc.right -= 4;

	CFont* oldFont = dc.SelectObject(&m_font);

	CSize ss2 = dc.GetTextExtent(" ", 1);

	mx.Lock();

	showarr.RemoveAll(); xarr.RemoveAll(); yarr.RemoveAll();
	offs.RemoveAll();

	int xx = rc.left, yy = 0;
		
	int alen = linearr.GetSize();

	for(int loop = 0; loop < alen; loop++)
		{
		CString val = linearr.GetAt(loop);
		
		//P2N("'%s'\r\n", val);

		CDWordArray offs3;
		CStringArray arr;

		ParseSpaces(&val, &arr, &offs3);
	
		int alen2 = arr.GetSize();
		for(int loop2 = 0; loop2 < alen2; loop2++)
			{
			CString val2 = arr.GetAt(loop2);

			int offx = offs2.GetAt(loop) + offs3.GetAt(loop2);

			//P2N("%d %d %d  '%s'\r\n", xx, yy, offx, val2);

			offs.Add(offx);
			showarr.Add(val2);
			
			CSize ss = dc.GetTextExtent(val2);
			
			// line break
			if(xx + ss.cx > rc.right)
				{
				xx = rc.left; yy += ss.cy;
				}

			xarr.Add(xx); yarr.Add(yy);

			if(xx + ss.cx <= rc.right)
				{
				xx += ss.cx; xx += ss2.cx;
				}
			}

		// New line here
		yy += ss2.cy;
		xx = rc.left;
		}

	mx.Unlock();

}

//////////////////////////////////////////////////////////////////////////

void CTextProg::OnTimer(UINT nIDEvent) 

{
	if(nIDEvent == 1)
		{
		KillTimer(nIDEvent);
		//P2N("CTextProg::OnTimer -- Invalidate timer\r\n");
		Invalidate();	
		}	
	CStatic::OnTimer(nIDEvent);
}

void CTextProg::OnSize(UINT nType, int cx, int cy) 

{
	//CStatic::OnSize(nType, cx, cy);
	
	ReScan();
	SetTimer(1, 300, NULL);
}
