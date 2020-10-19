#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<SFML\Graphics.hpp>
#include<iostream>
#include"Network.h"
class cScreen
{
private:
	SOCKET sock;
	sockaddr_in serverAddr;
public:
	
	virtual int Run(sf::RenderWindow &App) = 0;
};

