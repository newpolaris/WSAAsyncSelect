#pragma once

#include "Socket.h"
#include <windef.h>

class CWSAAsyncSelectDlg;

namespace echoservice {

	class Server : public Socket, public IServer
	{
	public:
		Server() {}
		virtual ~Server() {}
		void InitSocket(HWND hWnd);
		bool Run() override;
		void Listen() override;
	private:
		HWND m_hWnd = nullptr;
		CWSAAsyncSelectDlg* m_pMainDlg = nullptr;
	};

} // namespace echoservice {