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

	void Server::Listen()
	{
		sockaddr_in sockaddrServer;
		sockaddrServer.sin_family = AF_INET;
		sockaddrServer.sin_addr.s_addr = htonl(INADDR_ANY);
		sockaddrServer.sin_port = htons(info::nPort);

		int nBindRet = bind(m_socket, reinterpret_cast<sockaddr*>(&sockaddrServer), sizeof(sockaddr));
		if (nBindRet != 0)
			throw NetworkExcpetion("BIND_ERROR WITH ERROR_CODE " + std::to_string(nBindRet));

		int nListenRet = listen(m_socket, info::nBacklog);
		if (nListenRet != 0)
			throw NetworkExcpetion("Listen ERROR WITH ERROR_CODE " + std::to_string(nListenRet));
	}

	bool Server::Run()
	{
		static int nAddrLen = sizeof(sockaddr_in);

		sockaddr_in sockaddrClient;
		SOCKET sc = accept(m_socket, reinterpret_cast<sockaddr*>(&sockaddrClient), &nAddrLen);

		if (sc == INVALID_SOCKET)
			throw NetworkExcpetion("Accept error");

		auto destructor = [&](SOCKET* sc) { CloseSocket(sc, false); };
		std::unique_ptr<SOCKET, decltype(destructor)> _(&sc, destructor);

		while (true)
		{
			std::vector<char> buffer(1024, 0);
			auto nRecvRet = recv(sc, buffer.data(), buffer.size(), 0);
			if (nRecvRet == 0)
				return false;

			if (nRecvRet == SOCKET_ERROR)
				throw NetworkExcpetion("Recvied data - socket error");

			std::vector<char> recived(buffer.data(), buffer.data() + nRecvRet);

			std::cout << "RECIVED FROM CLINET: " << string(recived.begin(), recived.end()) << std::endl;
			int nSendLen = send(sc, recived.data(), buffer.size(), 0);
			if (nSendLen == SOCKET_ERROR)
				throw NetworkExcpetion("Send data - socket error");
		}
	}

} // namespace echoservice {