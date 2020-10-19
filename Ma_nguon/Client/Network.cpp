#include "Network.h"
#include<stdio.h>


Network::Network()
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData))
		printf("Version is not supported\n");

	int SERVER_PORT = 5500;
	char* SERVER_ADDR = "127.0.0.1";


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

}


Network::~Network()
{
	closesocket(this->sock);
}
SOCKET Network::getSock()
{
	return this->sock;
}
int Network::Connect(SOCKET sock, sockaddr_in serverAddr)
{
	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr))) return 0;
	else return -1;
}
sockaddr_in Network::getServerAddr()
{
	return this->serverAddr;
}