#include "stdafx.h"

#include <winsock2.h>
#include "Socket.h"
#include "Exception.h"

namespace echoservice {

Socket::Socket() : m_socket(INVALID_SOCKET) {}
Socket::~Socket()
{
	if (m_socket != INVALID_SOCKET)
		CloseSocket(&m_socket);

	WSACleanup();
}

void Socket::InitSocket()
{
	WSADATA wsaData;
	int nStartUpRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nStartUpRet != 0)
		throw NetworkExcpetion("Can't initalize WSA");

	auto sc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sc == INVALID_SOCKET)
		throw NetworkExcpetion("INVALIDE_SOCKET");

	m_socket = sc;
}

void Socket::CloseSocket(SOCKET* sc, bool force)
{
	if (sc == nullptr || *sc == INVALID_SOCKET) return;

	struct linger stLinger = { 0, 0 }; // SO_DONTLINGER로 설정
	// bIsForce가 true이면 SO_LINGER, timeout = 0으로 설정하여
	// 강제 종료 시킨다. 주의 테이터 손실이 있을 수 있다.
	if (force == true)
		stLinger.l_onoff = 1;

	// 소켓의 데이터 송수신을 모두 중단 시킨다.
	shutdown(*sc, SD_BOTH);

	// 소켓 옵션을 설정한다.
	setsockopt(*sc, SOL_SOCKET, SO_LINGER,
		reinterpret_cast<char*>(&stLinger), sizeof(stLinger));

	// 소켓 연결을 종료 시킨다.
	closesocket(*sc);

	*sc = INVALID_SOCKET;
}

} // namespace echoservice {