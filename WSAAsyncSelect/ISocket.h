#pragma once

#include <string>

namespace echoservice
{
	__interface ISocket
	{
		virtual void InitSocket() = 0;
		virtual void CloseSocket(SOCKET*, bool) = 0;
	};

	__interface IServer
	{
		virtual void Listen() = 0;
		virtual bool Run() = 0;
	};

	__interface IClient
	{
		virtual void Connect(std::string& ip, int port);
	};
}