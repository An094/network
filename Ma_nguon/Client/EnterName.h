#pragma once
#include"cScreen.h"
#include<iostream>
#include"SFML\Graphics.hpp"
#include"Textbox.h"
class EnterName
{
private:
	sf::Font font;

	sf::Text nameplayertxt;

	sf::Texture borderTexture;
	sf::Sprite borderSprite;

	sf::Texture enterTexture;
	sf::Sprite enterSprite;

	SOCKET sock;
	sockaddr_in serverAddr;
public:
	EnterName(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr);
	~EnterName();
	virtual int Run(sf::RenderWindow &window);
};

