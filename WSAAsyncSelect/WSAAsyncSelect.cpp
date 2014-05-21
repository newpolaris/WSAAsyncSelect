#include "stdafx.h"
#include "WSAAsyncSelect.h"
#include "WSAAsyncSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CWSAAsyncSelectApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CWSAAsyncSelectApp::CWSAAsyncSelectApp()
{
}

// The one and only CWSAAsyncSelectApp object
CWSAAsyncSelectApp theApp;

// CWSAAsyncSelectApp initialization
BOOL CWSAAsyncSelectApp::InitInstance()
{
	CWinApp::InitInstance();

	CWSAAsyncSelectDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

