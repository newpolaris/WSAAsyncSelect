#pragma once

#include "ISocket.h"

namespace echoservice
{
	class Socket : public ISocket
	{
	private:
		Socket(const Socket&);
		const Socket& operator=(const Socket&);

	protected:
		void CloseSocket(SOCKET* sc, bool force = false) override;

	public:
		Socket();
		virtual ~Socket();
		void InitSocket() override;

	protected:
		SOCKET m_socket;
	};
}
