#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define BUFF_SIZE 2048
#define MAX_ARRAY 50
#pragma comment(lib,"Ws2_32.lib")
class Network
{
private:
	SOCKET sock;
	sockaddr_in serverAddr;
public:
	Network();
	~Network();
	int Connect(SOCKET, sockaddr_in);
	SOCKET getSock();
	sockaddr_in getServerAddr();
};

