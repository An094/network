#pragma once
#include"cScreen.h"

class Gameplay:public cScreen
{
private:
	//int point;
	SOCKET	sock;
	sockaddr_in serverAddr;

	sf::Font font;
	sf::Texture imageTexture;
	sf::Text nameDisplay;
	sf::Text pointDisplay;
	sf::Texture ques;
	sf::Sprite question;
	sf::Text textQues;
	sf::Text textA;
	sf::Text textB;
	sf::Text textC;
	sf::Text textD;

	sf::Texture Button;
	sf::Sprite ButtonImageA;
	sf::Sprite ButtonImageB;
	sf::Sprite ButtonImageC;
	sf::Sprite ButtonImageD;
	
	int point;
	std::string name;



public:
	Gameplay(sf::RenderWindow & window, SOCKET sock, sockaddr_in serverAddr,int point,std::string name);
	~Gameplay();
	int getPoint();
	void setPoint(int p);
	virtual int Run(sf::RenderWindow &window);
};

