#include "stdafx.h"
#include <map>
#include <string>
#include "Exception.h"

namespace echoservice {
	using std::string;

	namespace enumToString
	{
		string& WSAError(int code)
		{
			static std::map<int, string> map =
			{
				{ WSAEINTR, "Interrupted function call." },
				{ WSAEBADF, "File handle is not valid." },
				{ WSAECONNRESET, "Connection reset by peer." },
				{ WSAECONNREFUSED, "Connection refused." }
			};

			static string invalid("Invalid error code or unknown");

			if (map.find(code) == map.end()) return invalid;
			else return map[code];
		}
	};

	NetworkException::NetworkException(const char* msg)
	{
		Message(string(msg));
	}

	NetworkException::NetworkException(string&& msg)
	{
		Message(msg);
	}

	const char* NetworkException::what() const throw() {
		return message.c_str();
	}

	void NetworkException::Message(string msg)
	{
		message = "[" + string(__FILE__) + "][" + std::to_string(__LINE__) + "]"
			+ msg + " " + enumToString::WSAError(WSAGetLastError())
			+ "code :" + std::to_string(WSAGetLastError());
	}
} // namespace echoservice {