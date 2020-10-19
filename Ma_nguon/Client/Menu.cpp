#include "Menu.h"
#include"EnterName.h"
#include"HighScore.h"

Menu::Menu(float width, float height,SOCKET sock, sockaddr_in serverAddr)
{
	this->sock = sock;
	this->serverAddr = serverAddr;
	if (!font.loadFromFile("MATURASC.TTF"))
	{
		//handle error
		printf("Error font!\n");
	}

	
	if (!logo.loadFromFile("Image/logo.png"))
	{
		std::cout << "Error loading file" << std::endl;
	}

	
	logoImage.setTexture(logo);
	logoImage.setPosition(sf::Vector2f(330.0f, 50.0f));

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2 -30, height / (MAX_NUMBER_OF_ITEMS) * 1+150));
	
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Score");
	menu[1].setPosition(sf::Vector2f(width / 2 -40, height / (MAX_NUMBER_OF_ITEMS) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Quit");
	menu[2].setPosition(sf::Vector2f(width / 2 - 30, height / (MAX_NUMBER_OF_ITEMS) * 3 -150));


	
	button.loadFromFile("Image/button.png");

	
	menuImage[0].setTexture(button);
	menuImage[0].setPosition(sf::Vector2f(width / 2-150, height / (MAX_NUMBER_OF_ITEMS) * 1+70));
	menuImage[0].setScale(sf::Vector2f(1.0f, 2.0f));
	menuImage[0].scale(sf::Vector2f(0.3f, 0.1f));

	menuImage[1].setTexture(button);
	menuImage[1].setPosition(sf::Vector2f(width / 2-150, height / (MAX_NUMBER_OF_ITEMS) * 2-85));
	menuImage[1].setScale(sf::Vector2f(1.0f, 2.0f));
	menuImage[1].scale(sf::Vector2f(0.3f, 0.1f));

	
	menuImage[2].setTexture(button);
	menuImage[2].setPosition(sf::Vector2f(width / 2 - 150, height / (MAX_NUMBER_OF_ITEMS) * 3 -230));
	menuImage[2].setScale(sf::Vector2f(1.0f, 2.0f));
	menuImage[2].scale(sf::Vector2f(0.3f, 0.1f));




	
}


Menu::~Menu()
{
}
void Menu::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(80, 240, 180));
	window.draw(logoImage);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		
		window.draw(menuImage[i]);
		window.draw(menu[i]);
	}
	window.display();
}
int Menu::Run(sf::RenderWindow &window)
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
					float btnPosY0 = 430;

					float btnPosX1 = 360;
					float btnPosY1 = 580;

					float btnPosX2 = 360;
					float btnPosY2 = 730;

					float btnxPosWidth0 = 645;
					float btnyPosHeight0 = 510;

					float btnxPosWidth1 = 645;
					float btnyPosHeight1 = 655;

					float btnxPosWidth2 = 645;
					float btnyPosHeight2 = 800;

					if (mouseX<btnxPosWidth0 && mouseX>btnPosX0 && mouseY<btnyPosHeight0 && mouseY>btnPosY0)
					{
						menuImage[0].setColor(sf::Color(250, 20, 20));
						menu[0].setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						menuImage[0].setColor(sf::Color(255, 255, 255));
						menu[0].setFillColor(sf::Color::White);
					}
					if (mouseX<btnxPosWidth1 && mouseX>btnPosX1 && mouseY<btnyPosHeight1 && mouseY>btnPosY1)

					{
						
						menuImage[1].setColor(sf::Color(250, 20, 20));
						menu[1].setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						menuImage[1].setColor(sf::Color(255, 255, 255));
						menu[1].setFillColor(sf::Color::White);
					}

					if (mouseX<btnxPosWidth2 && mouseX>btnPosX2 && mouseY<btnyPosHeight2 && mouseY>btnPosY2)

					{

						menuImage[2].setColor(sf::Color(250, 20, 20));
						menu[2].setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						menuImage[2].setColor(sf::Color(255, 255, 255));
						menu[2].setFillColor(sf::Color::White);
					}
					
					


				}
				break;
				case sf::Event::MouseButtonPressed:
				{
				
					float mouseX = sf::Mouse::getPosition(window).x;
					float mouseY = sf::Mouse::getPosition(window).y;

					float btnPosX0 = 360;
					float btnPosY0 = 430;

					float btnPosX1 = 360;
					float btnPosY1 = 580;

					float btnPosX2 = 360;
					float btnPosY2 = 730;

					float btnxPosWidth0 = 645;
					float btnyPosHeight0 = 510;

					float btnxPosWidth1 = 645;
					float btnyPosHeight1 = 655;

					float btnxPosWidth2 = 645;
					float btnyPosHeight2 = 800;
					
					if (mouseX<btnxPosWidth0 && mouseX>btnPosX0 && mouseY<btnyPosHeight0 && mouseY>btnPosY0)
					{
						EnterName enterGame(window, this->sock, this->serverAddr);
						enterGame.Run(window);
					}
					if (mouseX<btnxPosWidth1 && mouseX>btnPosX1 && mouseY<btnyPosHeight1 && mouseY>btnPosY1)
					{
						printf("HIGH SCORE");
						HighScore highcore(window, this->sock, this->serverAddr);
						highcore.Run(window);
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