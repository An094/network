#pragma once
#include"cScreen.h"
#include"Gameplay.h"
class Gameover:public cScreen
{
public:
	Gameover(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr,int point,std::string name);
	~Gameover();
	void draw(sf::RenderWindow &window);
	virtual int Run(sf::RenderWindow &window);

private:
	SOCKET sock;
	sockaddr_in serverAddr;
	std::string name;
	sf::Font font;
	sf::Text yourPoint;
	sf::Text conttxt;
	sf::Text mainMenutxt;
	sf::Text quittxt;
	sf::Texture logoGameOver;
	sf::Texture button;
	sf::Sprite logoImange;
	sf::Sprite contButtonImage;
	sf::Sprite mainMenuButtonImage;
	sf::Sprite quitButtonImage;
};

