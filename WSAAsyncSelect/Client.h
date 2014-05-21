#pragma once 

#include "Socket.h"
#include <string>

namespace echoservice {
	using std::string;

	class Client : public Socket, public IClient
	{
	public:
		Client() {}
		virtual ~Client() {}
		void Connect(string& ip, int port) override;
	};


} // namespace echoservice {