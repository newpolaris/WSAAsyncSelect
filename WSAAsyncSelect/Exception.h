#pragma once

#include <iosfwd>
#include <string>

namespace echoservice {
	class NetworkException : public std::exception
	{
	public:
		explicit NetworkException(const char* msg);
		explicit NetworkException(std::string&& msg);
		virtual const char* what() const throw();

	private:
		void Message(std::string msg);
		std::string message;
	};
}