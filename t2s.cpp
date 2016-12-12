// t2s.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"


#include "t2s.h"
#include "t2sDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "objbase.h"

int *gpIVTxt = NULL;

#if 0

// ReleaseInterface - displays an error message and releases the 
// voice-text object.
// Returns FALSE.
// szMsg - text of error message
//
// Global variable:
// gpIVTxt - address of voice-text interface

BOOL ReleaseInterfaces(const char *szMsg)

{
	// If a message is specified, display it.
	if (*szMsg)
		MessageBox(NULL, szMsg, NULL, MB_OK);

	if(gpIVTxt)
		gpIVTxt->Release();

	gpIVTxt = NULL;

	return FALSE;
}


// BeginOLE - initializes OLE, creates a voice-text object, and 
// registers the application with the object.
// Returns TRUE if successful or FALSE otherwise.
// 
// Global variables:
// gpIVTxt - address of IVoiceText interface
// gpIVTxtAttr - address of IVTxtAttributes interface
// gpVTxtNotifySink - address of IVTxtNotifySink interface

BOOL BeginOLE()

{
	HRESULT hRes;

	// Initialize OLE.

	if (FAILED(CoInitialize(NULL)))
		return ReleaseInterfaces("CoInitialize() failed.");

	// Create a voice-text object.

	if (CoCreateInstance(CLSID_VTxt, NULL, CLSCTX_LOCAL_SERVER, 
			IID_IVoiceText, (LPVOID *) &gpIVTxt) != S_OK)
		return ReleaseInterfaces(
			"Error in CoCreateInstance for voice-text interface." );


	// Get the address of the voice-text attributes interface.

	hRes = gpIVTxt->QueryInterface(IID_IVTxtAttributes, 

	(LPVOID FAR *) &gpIVTxtAttr);

	if (FAILED(hRes)) 
		return ReleaseInterfaces(
			"Failed to get voice-text attributes interface.");


	// Create and register the voice-text notification sink.
	gpVTxtNotifySink = new CIVTxtNotifySink;

	if (gpVTxtNotifySink == NULL)
		return ReleaseInterfaces(
			"Out of memory for voice-text notification object.");


	hRes = gpIVTxt->Register(NULL, "SRClock", gpVTxtNotifySink, 
			IID_IVTxtNotifySink, VTXTF_ALLMESSAGES, NULL);

	if (FAILED(hRes))
		return ReleaseInterfaces(
			"Failed to register voice-text notification sink.");

		return TRUE;
}

#endif




/////////////////////////////////////////////////////////////////////////////
// CT2sApp

BEGIN_MESSAGE_MAP(CT2sApp, CWinApp)
	//{{AFX_MSG_MAP(CT2sApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT2sApp construction

CT2sApp::CT2sApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CT2sApp object

CT2sApp theApp;
int	IVoiceText;

/////////////////////////////////////////////////////////////////////////////
// CT2sApp initialization

BOOL CT2sApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	//VERIFY(::CoInitialize(NULL));

	::CoInitialize(NULL);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CT2sDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


#if 0


#include <stdafx.h>
#include <sapi.h>

int main(int argc, char* argv[])
{
    
    if (FAILED(::CoInitialize(NULL)))
        return FALSE;

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice;);
    if( SUCCEEDED( hr ) )
    {
        hr = pVoice->Speak(L"Hello world", 0, NULL);
        pVoice->Release();
        pVoice = NULL;
    }

    ::CoUninitialize();
    return TRUE;
}

#endif

int CT2sApp::ExitInstance() 
{
	::CoUninitialize();	
	return CWinApp::ExitInstance();
}
