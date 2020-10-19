#include <SFML\Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Gameplay.h"
#include "Gameover.h"
#include "Network.h"
#include "EnterName.h"
#include "HighScore.h"
int main()
{
	
	Network* net=new Network();
	SOCKET sock = net->getSock();
	sockaddr_in serverAddr = net->getServerAddr();


	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error! Cannot connect server. %d", WSAGetLastError());
	}
	else
	{
		printf("Connect successfull");
	}

	std::vector<cScreen*> Screens;
	int nextScreen = 0;
	sf::RenderWindow window(sf::VideoMode(1000, 900), "Hay chon gia dung", sf::Style::Close | sf::Style::Titlebar);
	
	Menu menu(1000, 900, sock, serverAddr);
	menu.Run(window);

	return EXIT_SUCCESS;
}
