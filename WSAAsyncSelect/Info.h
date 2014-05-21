#pragma once
#include <string>

namespace echoservice
{
	enum USER_MSG { WM_SOCKETMSG = WM_USER + 1 };

	enum RESULT
	{
		kSUCCESS = 0,
		kFAIL = -1
	};

	namespace info
	{
		static int nPort = 1234;
		static int nBacklog = 5; // server waiting queue size.
		static std::string serverIP("127.0.0.1");
	};

};
