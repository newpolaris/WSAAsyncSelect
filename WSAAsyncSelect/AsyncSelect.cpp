#include "stdafx.h"

#include <string>
#include <iostream>
#include <exception>

#include "Exception.h"
#include "Server.h"
#include "Client.h"
#include "Info.h"

int main(int argc, char** argv)
{
	using std::string;
	using std::cout;
	using std::endl;
	
	bool isServer = false;

	if (argc == 2 && (string(argv[1]).compare("/server") ||
				      string(argv[1]).compare("/client")))
	{
		isServer = string(argv[1]).compare("/server") == 0;
	}
	else if (argc == 1)
	{
		string input;
		getline(std::cin, input);
		if (input.compare("server") == 0)
			isServer = true;
		else if (input.compare("client") == 0)
			isServer = false;
	}
	else
	{
		std::cout << "Invalide option parameter" << std::endl; 
		return echoservice::kFAIL;
	}

	if (isServer)
	{
		echoservice::Server server;
		try {
			server.InitSocket();
			server.Listen();

			bool bRelunch = true;
			do
			{
				try 
				{
					bRelunch = server.Run();
				}
				catch (echoservice::NetworkExcpetion& e)
				{
					cout << "EXCEPTION : " << e.what() << endl;
					cout << "RETRY CONNETCTION" << endl;
				}
			} while (bRelunch);
		}
		catch (std::exception& e) {
			cout << "EXCEPTION : " << e.what() << endl;
		}
	}
	else
	{
		echoservice::Client client;
		try {
			client.InitSocket();
			client.Connect(echoservice::info::serverIP, echoservice::info::nPort);
		}
		catch (echoservice::NetworkExcpetion& e)
		{
			cout << "EXCEPTION : " << e.what() << endl;
		}
		catch (std::exception& e) 
		{
			cout << "EXCEPTION : " << e.what() << endl;
		}
	}

	return echoservice::kSUCCESS;
}