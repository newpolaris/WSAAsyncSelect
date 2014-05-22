#include "stdafx.h"
#include "WSAAsyncSelect.h"
#include "WSAAsyncSelectDlg.h"
#include "afxdialogex.h"
#include "Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "Exception.h"

CWSAAsyncSelectDlg::CWSAAsyncSelectDlg(CWnd* pParent)
	: CDialog(IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_out.init(&m_ctOutput);
}

void CWSAAsyncSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_ctOutput);
}

BEGIN_MESSAGE_MAP(CWSAAsyncSelectDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(echoservice::WM_SOCKETMSG, &CWSAAsyncSelectDlg::OnSocketMsg)
	ON_BN_CLICKED(ID_START_SERVER, &CWSAAsyncSelectDlg::OnBnClickedStartServer)
END_MESSAGE_MAP()


// CWSAAsyncSelectDlg message handlers

BOOL CWSAAsyncSelectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWSAAsyncSelectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWSAAsyncSelectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CWSAAsyncSelectDlg::OnSocketMsg(WPARAM wParam, LPARAM lParam)
{
	using std::string;
	using std::vector;
	using echoservice::m_endl;
	using echoservice::NetworkException;

	auto socket = static_cast<SOCKET>(wParam);

	try {
		auto nWSASelectErrorRet = WSAGETSELECTERROR(lParam);

		if (nWSASelectErrorRet != 0)
			throw NetworkException("WSA_GET_SELECT_ERROR");

		std::function<bool(SOCKET)> send_data = [this](SOCKET socket)
		{
			int nSendLen = send(socket, m_send_buffer.data(), m_send_buffer.size(), 0);
			if (nSendLen == SOCKET_ERROR)
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					throw NetworkException("Send data - socket error");
				else return false;

			m_send_buffer.clear();
			return true;
		};

		auto nEvent = WSAGETSELECTEVENT(lParam);
		switch (nEvent)
		{
		case FD_ACCEPT:
		{
			static int nAddrLen = sizeof(sockaddr_in);

			sockaddr_in sockaddrClient;
			SOCKET sc = accept(socket, reinterpret_cast<sockaddr*>(&sockaddrClient), &nAddrLen);

			if (sc == INVALID_SOCKET)
				throw NetworkException("Accept error");
			break;
		}

		case FD_READ:
		{
			vector<char> buffer(1024, 0);
			auto nRecvRet = recv(socket, buffer.data(), buffer.size(), 0);
			if (nRecvRet == 0)
			{
				m_out << "Disconnected with client." << m_endl;
				m_server->CloseSocket(&socket);
				return false;
			}

			if (nRecvRet == SOCKET_ERROR)
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					throw NetworkException("Recvied data - socket error");
				else break;

			m_send_buffer = vector<char>(buffer.data(), buffer.data() + nRecvRet);

			m_out << "RECIVED FROM CLINET: " << string(m_send_buffer.begin(), m_send_buffer.end()) << m_endl;
			send_data(socket);
			break;
		}
		case FD_WRITE:
		{
			if (m_send_buffer.size() <= 0) break;

			send_data(socket);
		}

		case FD_CLOSE:
		{
			m_out << "Client shut down connection" << m_endl;
			m_server->CloseSocket(&socket);
			break;
		}
		}
	}
	catch (std::exception& e) {
		m_server->CloseSocket(&socket);
		m_out << "EXCEPTION : " << e.what() << m_endl;
	}

	return true;
}


void CWSAAsyncSelectDlg::OnBnClickedStartServer()
{
	using echoservice::m_endl;

	try {
		if (m_server == nullptr)
			m_server.reset(new echoservice::Server());

		if (m_server == nullptr)
			throw echoservice::NetworkException("Server memory initialize error");

		m_server->InitSocket(m_hWnd);
		m_server->Listen();
		m_server->Run();
	}
	catch (echoservice::NetworkException& e) {
		m_out << "EXCEPTION : " << e.what() << m_endl;
		m_out << "RETRY CONNETCTION" << m_endl;
	}
	catch (std::exception& e) {
		m_out << "EXCEPTION : " << e.what() << m_endl;
	}
}