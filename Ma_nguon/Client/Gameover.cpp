#include "Gameover.h"
#include "Gameplay.h"
#include "Menu.h"

Gameover::Gameover(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr, int point,std::string name)
{
	this->sock = sock;
	this->serverAddr = serverAddr;
	this->name = name;
	
	if (!font.loadFromFile("MATURASC.TTF"))
	{
		std::cout << "Loading font error" << std::endl;
	}
	
	yourPoint.setFont(font);
	yourPoint.setCharacterSize(40);
	yourPoint.setPosition(sf::Vector2f(350.0f, 400.0f));
	std::string Point = "Your Point: "+ std::to_string(point);
	yourPoint.setString(Point);

	logoGameOver.loadFromFile("Image/game-over.png");
	logoImange.setTexture(logoGameOver);
	logoImange.setPosition(sf::Vector2f(300.0f, 150.0f));

	conttxt.setFont(font);
	conttxt.setFillColor(sf::Color::White);
	conttxt.setString("Retry");
	conttxt.setPosition(sf::Vector2f(460.0f, 500.0f));

	mainMenutxt.setFont(font);
	mainMenutxt.setFillColor(sf::Color::White);
	mainMenutxt.setString("Menu");
	mainMenutxt.setPosition(sf::Vector2f(460.0f, 650.0f));

	quittxt.setFont(font);
	quittxt.setFillColor(sf::Color::White);
	quittxt.setString("Quit");
	quittxt.setPosition(sf::Vector2f(470.0f, 800.0f));



	button.loadFromFile("Image/button.png");


	contButtonImage.setTexture(button);
	contButtonImage.setPosition(sf::Vector2f(350.0f, 420.0f));
	contButtonImage.setScale(sf::Vector2f(1.0f, 2.0f));
	contButtonImage.scale(sf::Vector2f(0.3f, 0.1f));

	mainMenuButtonImage.setTexture(button);
	mainMenuButtonImage.setPosition(sf::Vector2f(350.0f, 570.0f));
	mainMenuButtonImage.setScale(sf::Vector2f(1.0f, 2.0f));
	mainMenuButtonImage.scale(sf::Vector2f(0.3f, 0.1f));

	quitButtonImage.setTexture(button);
	quitButtonImage.setPosition(sf::Vector2f(350.0f, 715.0f));
	quitButtonImage.setScale(sf::Vector2f(1.0f, 2.0f));
	quitButtonImage.scale(sf::Vector2f(0.3f, 0.1f));
}


Gameover::~Gameover()
{
}
void Gameover::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(80, 240, 180));
	window.draw(yourPoint);
	window.draw(logoImange);
	window.draw(contButtonImage);
	window.draw(mainMenuButtonImage);
	window.draw(quitButtonImage);
	window.draw(conttxt);
	window.draw(mainMenutxt);
	window.draw(quittxt);

	window.display();

	
}

int Gameover::Run(sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
				case sf::Event::Closed:
					window.close();
				case sf::Event::MouseMoved:
				{
					float mouseX = sf::Mouse::getPosition(window).x;
					float mouseY = sf::Mouse::getPosition(window).y;

					float btnPosX0 = 360;
					float btnPosY0 = 480;

					float btnPosX1 = 360;
					float btnPosY1 = 630;

					float btnPosX2 = 360;
					float btnPosY2 = 780;

					float btnxPosWidth0 = 645;
					float btnyPosHeight0 = 560;

					float btnxPosWidth1 = 645;
					float btnyPosHeight1 = 700;

					float btnxPosWidth2 = 645;
					float btnyPosHeight2 = 850;


					if (mouseX<btnxPosWidth0 && mouseX>btnPosX0 && mouseY<btnyPosHeight0 && mouseY>btnPosY0)
					{
						contButtonImage.setColor(sf::Color(250, 20, 20));
						conttxt.setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						contButtonImage.setColor(sf::Color(255, 255, 255));
						conttxt.setFillColor(sf::Color::White);
					}
					if (mouseX<btnxPosWidth1 && mouseX>btnPosX1 && mouseY<btnyPosHeight1 && mouseY>btnPosY1)

					{

						mainMenuButtonImage.setColor(sf::Color(250, 20, 20));
						mainMenutxt.setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						mainMenuButtonImage.setColor(sf::Color(255, 255, 255));
						mainMenutxt.setFillColor(sf::Color::White);
					}

					if (mouseX<btnxPosWidth2 && mouseX>btnPosX2 && mouseY<btnyPosHeight2 && mouseY>btnPosY2)

					{

						quitButtonImage.setColor(sf::Color(250, 20, 20));
						quittxt.setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						quitButtonImage.setColor(sf::Color(255, 255, 255));
						quittxt.setFillColor(sf::Color::White);
					}

					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					float mouseX = sf::Mouse::getPosition(window).x;
					float mouseY = sf::Mouse::getPosition(window).y;

					float btnPosX0 = 360;
					float btnPosY0 = 480;

					float btnPosX1 = 360;
					float btnPosY1 = 630;

					float btnPosX2 = 360;
					float btnPosY2 = 780;

					float btnxPosWidth0 = 645;
					float btnyPosHeight0 = 560;

					float btnxPosWidth1 = 645;
					float btnyPosHeight1 = 700;

					float btnxPosWidth2 = 645;
					float btnyPosHeight2 = 850;


					
					if (mouseX<btnxPosWidth0 && mouseX>btnPosX0 && mouseY<btnyPosHeight0 && mouseY>btnPosY0)
					{
						Gameplay gameplay(window, this->sock, this->serverAddr,0,this->name);
						gameplay.Run(window);
					}
					
					if (mouseX<btnxPosWidth1 && mouseX>btnPosX1 && mouseY<btnyPosHeight1 && mouseY>btnPosY1)
					{
						Menu menu(1000.0f, 900.0f, this->sock, this->serverAddr);
						menu.Run(window);
					}

					if (mouseX<btnxPosWidth2 && mouseX>btnPosX2 && mouseY<btnyPosHeight2 && mouseY>btnPosY2)

					{
						window.close();
					}
					
				}
				break;
			}
			
		}
		this->draw(window);
		
	}
	return 0;
}