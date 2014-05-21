#pragma once

#include <iosfwd>
#include <string>

namespace echoservice {
	class NetworkExcpetion : public std::exception
	{
	public:
		explicit NetworkExcpetion(const char* msg);
		explicit NetworkExcpetion(std::string&& msg);
		virtual const char* what() const throw();

	private:
		void Message(std::string msg);
		std::string message;
	};
}