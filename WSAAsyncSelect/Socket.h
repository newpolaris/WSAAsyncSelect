#pragma once

#include "ISocket.h"

namespace echoservice
{
	class Socket : public ISocket
	{
	private:
		Socket(const Socket&);
		const Socket& operator=(const Socket&);

	public:
		Socket();
		virtual ~Socket();
		void InitSocket() override;
		void CloseSocket(SOCKET* sc, bool force = false) override;

	protected:
		SOCKET m_socket;
	};
}
