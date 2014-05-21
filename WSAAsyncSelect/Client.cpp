#include "stdafx.h"

#include <vector>
#include <iostream>
#include "Client.h"
#include "Exception.h"

namespace echoservice {
	using std::cin;
	using std::vector;

	void Client::Connect(string& ip, int port)
	{
		SOCKADDR_IN stSeverAddr;

		stSeverAddr.sin_family = AF_INET;
		stSeverAddr.sin_port = htons(port);
		stSeverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

		int nConnectRet = connect(m_socket, reinterpret_cast<sockaddr*>(&stSeverAddr),
			sizeof(sockaddr));

		if (nConnectRet == SOCKET_ERROR)
			throw NetworkExcpetion("Connet error");

		while (true)
		{
			std::cout << ">> ";
			string str;
			str.reserve(1024);
			getline(cin, str);

			if (str.compare("QUIT()") == 0)
				break;

			vector<char> buffer(1024, 0);
			auto sentLength = min(buffer.size(), str.size());
			copy_n(str.begin(), sentLength, buffer.begin());

			int nSendRet = send(m_socket, buffer.data(), sentLength, 0);

			if (nSendRet == SOCKET_ERROR)
				throw NetworkExcpetion("Send error");

			int nRecvRet = recv(m_socket, buffer.data(), buffer.size(), 0);
			if (nRecvRet == 0)
				return;

			if (nRecvRet == SOCKET_ERROR)
				throw NetworkExcpetion("Recv error");

			if (nRecvRet > 0)
				std::cout << "RECEVIED FROM CLIENT: " << string(buffer.data(), buffer.data() + nSendRet) << std::endl;
		}
	}

} // namespace echoservice {