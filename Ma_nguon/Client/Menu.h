#pragma once
#include"cScreen.h"
#define MAX_NUMBER_OF_ITEMS 3

class Menu:public cScreen
{
public:
	Menu(float width, float height,SOCKET sock,sockaddr_in serverAddr);
	~Menu();
	
	virtual int Run(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);


private:
	SOCKET sock;
	sockaddr_in serverAddr;

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite menuImage[MAX_NUMBER_OF_ITEMS];
	sf::Texture button;

	sf::Texture logo;
	sf::Sprite logoImage;
};

