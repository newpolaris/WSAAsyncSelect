#include "stdafx.h"

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "Info.h"
#include "Server.h"
#include "Exception.h"

namespace echoservice {
	using std::string;

	void Server::InitSocket(HWND hWnd)
	{
		Socket::InitSocket();
		m_hWnd = hWnd;
	}

	void Server::Listen()
	{
		sockaddr_in sockaddrServer;
		sockaddrServer.sin_family = AF_INET;
		sockaddrServer.sin_addr.s_addr = htonl(INADDR_ANY);
		sockaddrServer.sin_port = htons(info::nPort);

		int nBindRet = bind(m_socket, reinterpret_cast<sockaddr*>(&sockaddrServer), sizeof(sockaddr));
		if (nBindRet != 0)
			throw NetworkException("BIND_ERROR WITH ERROR_CODE " + std::to_string(nBindRet));

		int nListenRet = listen(m_socket, info::nBacklog);
		if (nListenRet != 0)
			throw NetworkException("Listen ERROR WITH ERROR_CODE " + std::to_string(nListenRet));
	}

	bool Server::Run()
	{
		int nSelectRet = WSAAsyncSelect(m_socket, m_hWnd, WM_SOCKETMSG, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE);

		if (nSelectRet == SOCKET_ERROR)
			throw NetworkException("WSAAsyncSelect error");

		return true;
	}

} // namespace echoservice {