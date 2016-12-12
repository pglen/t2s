// Speak.cpp: implementation of the CSpeak class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "t2s.h"
#include "Speak.h"
#include "mxpad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpeak::CSpeak()

{
	postto = 0;
	pVoice = NULL;
	thhevent = CreateEvent(NULL, 0, 0, NULL);	ASSERT(thhevent);
	thhandle = _beginthread(_Thread, 0, this); ASSERT(thhandle);
}

CSpeak::~CSpeak()

{
	CleanUp();
	//::CoUninitialize();
}

//////////////////////////////////////////////////////////////////////////

int	CSpeak::Speak(const TCHAR *str)

{
	memset(outp, 0, sizeof(outp));

	MultiByteToWideChar(CP_ACP, 0, str, strlen(str), (LPWSTR)outp, sizeof(outp)/ sizeof(TCHAR));
	//_tcscpy((TCHAR*)outp, str);
	SetEvent(thhevent);

	return 0;
}

int	CSpeak::Prop()

{
	HRESULT hr = S_OK;
	int fSupported = false;

    // display properties UI for the current TTS engine
    hr = pVoice->IsUISupported(SPDUI_EngineProperties, NULL, NULL, &fSupported);
    // Check hr

	P2N("DisplayUI supp=%d hr=%d %d\r\n", fSupported, hr, S_OK);
    	
    if(fSupported == TRUE)
		{
		hr = pVoice->DisplayUI(AfxGetMainWnd()->m_hWnd, 
					L"Voice", SPDUI_EngineProperties, NULL, NULL);

		P2N("DisplayUI hr=%d %d\r\n", hr, FAILED(hr));
    	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

void	CSpeak::Stop()

{
	TerminateThread((HANDLE)thhandle, 0);

	CleanUp();

	// Post stop status
	if(postto)
		{
		::PostMessage(postto, WM_USER + 1, SPRS_DONE, 0);												
		}

	// Restart the thead and init the COM interface again
	thhandle = _beginthread(_Thread, 0, this); ASSERT(thhandle);
}

//////////////////////////////////////////////////////////////////////////
// initialze TTS engine in the thread

void	CSpeak::_Thread(void *lpParam)

{
	CSpeak *ts = (CSpeak*)lpParam;

	// Make sure you call this in you app first
	if (FAILED(::CoInitialize(NULL)))
		{
		TRACE("Could not init COM\r\n");
		}

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, 
						(void **)&ts->pVoice);

	if( SUCCEEDED( hr ) )
		{
		//TRACE("Got voice subsystem\r\n");	
		}
		
	//////////////////////////////////////////////////////////////////////////

	while(true)
		{
		WaitForSingleObject(ts->thhevent, INFINITE);

		if(ts->pVoice)
			{
			//TRACE("_Thread event sound: '%S'\r\n", ts->outp);		
			
			HRESULT hr = ts->pVoice->Speak((LPCWSTR)ts->outp, SPF_ASYNC, NULL);

			SPVOICESTATUS ss;

			DWORD	ulInputWordLen = -1, ulInputWordPos = -1;

			while(true)
				{
				// Object vanished (async close)
				if(!ts->pVoice)
					break;

				ts->pVoice->GetStatus(&ss, NULL);

				//P2N("status run=%d pos=%d len=%d\r\n", 
				//			ss.dwRunningState, ss.ulInputWordPos, 
				//				ss.ulInputWordLen);

				if(ts->postto)
					{	
					// Changed?
					if(ulInputWordPos != ss.ulInputWordPos || 
							ulInputWordLen != ss.ulInputWordLen)
						{
						::PostMessage(ts->postto, WM_USER + 1, ss.dwRunningState,						
								(ss.ulInputWordPos << 16) + ss.ulInputWordLen);
						}
					ulInputWordPos = ss.ulInputWordPos;
					ulInputWordLen = ss.ulInputWordLen;
					}
			
				if(ss.dwRunningState  == SPRS_DONE)
					{
					if(ts->postto)
						{
						// Always post final one
						::PostMessage(ts->postto, WM_USER + 1, ss.dwRunningState,						
								(ss.ulInputWordPos << 16) + ss.ulInputWordLen);
						}
					break;
					}

				// Make the processor happy
				Sleep(100);
				}
			}
		}
}

//////////////////////////////////////////////////////////////////////////

void CSpeak::CleanUp()

{
	if(pVoice)
		{
		pVoice->Release();	pVoice = NULL;	
		}
}

//////////////////////////////////////////////////////////////////////////

void CSpeak::Skip(int num)

{
	DWORD nnn;

	pVoice->Skip(L"SENTENCE", num, &nnn);

}
