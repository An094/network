#include "EnterName.h"
#include"Gameplay.h"


EnterName::EnterName(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr)
{
	
	this->sock = sock;
	this->serverAddr = serverAddr;


	borderTexture.loadFromFile("Image/vienten.png");
	borderSprite.setTexture(borderTexture);
	borderSprite.setPosition(sf::Vector2f(280.0f, 400.0f));
	borderSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	borderSprite.scale(sf::Vector2f(0.7f, 0.2f));

	enterTexture.loadFromFile("Image/buttonenter.png");
	enterSprite.setTexture(enterTexture);
	enterSprite.setPosition(sf::Vector2f(330.0f, 530.0f));
	enterSprite.setScale(sf::Vector2f(1.0f, 2.0f));
	enterSprite.scale(sf::Vector2f(0.55f, 0.3f));
}


EnterName::~EnterName()
{
}

int EnterName::Run(sf::RenderWindow &window)
{
	
	if (!font.loadFromFile("MATURASC.TTF"))
	{
		//handle error
		printf("Error font!\n");
	}

	nameplayertxt.setFont(font);
	nameplayertxt.setCharacterSize(45);
	nameplayertxt.setFillColor(sf::Color::Red);
	nameplayertxt.setPosition(sf::Vector2f(320.0f, 340.0f));
	nameplayertxt.setString("_Ten nguoi choi:_");


	Textbox text1(30, sf::Color::Black, true);
	text1.setPosition(sf::Vector2f(370.0f, 420.0f));
	text1.setLimit(true, 20);
	text1.setFont(font);


	while (window.isOpen()) {

		sf::Event Event;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			text1.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			text1.setSelected(false);
		}
		
		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				text1.typedOn(Event);
			case sf::Event::MouseButtonPressed:
			{
				float mouseX = sf::Mouse::getPosition(window).x;
				float mouseY = sf::Mouse::getPosition(window).y;

				float btnPosX0 = 340;
				float btnPosY0 = 550;

				float btnxPosWidth0 = 660;
				float btnyPosHeight0 = 630;
				if (mouseX<btnxPosWidth0 && mouseX>btnPosX0 && mouseY<btnyPosHeight0 && mouseY>btnPosY0)
				{
					std::string name = text1.getText();
					Gameplay gameplay(window, this->sock, this->serverAddr, 0, name);
					gameplay.Run(window);
				}
			}
			}
		}
		window.clear(sf::Color(80, 240, 180));
		window.draw(borderSprite);
		window.draw(enterSprite);
		window.draw(nameplayertxt);
		text1.drawTo(window);
		window.display();
	}
	return 0;
}