#pragma once
#include "cScreen.h"
class HighScore:public cScreen
{
private:
	SOCKET sock;
	sockaddr_in serverAddr;
	
	sf::Texture logoTxt;
	sf::Sprite logoSprite;

	sf::Texture backTxt;
	sf::Sprite backSprite;

	sf::Font font;

	sf::Text player1Name;
	sf::Text player1Score;

	sf::Text player2Name;
	sf::Text player2Score;

	sf::Text player3Name;
	sf::Text player3Score;
public:
	HighScore(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr);
	~HighScore();
	void draw(sf::RenderWindow &window);
	virtual int Run(sf::RenderWindow &window);
};

