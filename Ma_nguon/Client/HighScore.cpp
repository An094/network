#include "HighScore.h"



HighScore::HighScore(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr)
{
	this->sock = sock;
	this->serverAddr = serverAddr;

	logoTxt.loadFromFile("Image/highscore.png");
	logoSprite.setTexture(logoTxt);
	logoSprite.setPosition(sf::Vector2f(350.0f, 50.0f));

	backTxt.loadFromFile("Image/back.png");
	backSprite.setTexture(backTxt);
	backSprite.setPosition(sf::Vector2f(430.0f, 750.0f));
	backSprite.setScale(sf::Vector2f(0.15f, 0.15f));

	if (!font.loadFromFile("MATURASC.TTF"))
	{
		//handle error
		printf("Error font!\n");
	}


}


HighScore::~HighScore()
{
}

int HighScore::Run(sf::RenderWindow &window)
{
	
	int ret = send(this->sock, "SCORE", 5, 0);
	char buff[BUFF_SIZE];
	ret = recv(this->sock, buff, BUFF_SIZE, 0);
	if (ret < 0)
	{
		printf("Error recv!");
	}
	buff[ret] = 0;
	char name1[BUFF_SIZE];
	char score1[BUFF_SIZE];

	char name2[BUFF_SIZE];
	char score2[BUFF_SIZE];

	char name3[BUFF_SIZE];
	char score3[BUFF_SIZE];

	int post = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
	for (int i = 5; i < ret; i++)
	{
		if (buff[i] == '|') post++;
		else if (post == 0)
		{
			name1[a++] = buff[i];
		}
		else if (post == 1)
		{
			score1[b++] = buff[i];
		}
		else if (post == 2)
		{
			name2[c++] = buff[i];
		}
		else if (post == 3)
		{
			score2[d++] = buff[i];
		}
		else if (post == 4)
		{
			name3[e++] = buff[i];
		}
		else if (post == 5)
		{
			score3[f++] = buff[i];
		}
	}
	name1[a] = 0;
	score1[b] = 0;
	name2[c] = 0;
	score2[d] = 0;
	name3[e] = 0;
	score3[f] = 0;

	puts(name1); puts(score1);
	puts(name2); puts(score2);
	puts(name3); puts(score3);


	player1Name.setFont(font);
	player1Name.setString(name1);
	player1Name.setCharacterSize(40);
	player1Name.setFillColor(sf::Color::Red);
	player1Name.setPosition(sf::Vector2f(200.0f, 300.0f));

	player1Score.setFont(font);
	player1Score.setString(score1);
	player1Score.setCharacterSize(40);
	player1Score.setFillColor(sf::Color::Red);
	player1Score.setPosition(sf::Vector2f(700.0f, 300.0f));

	player2Name.setFont(font);
	player2Name.setString(name2);
	player2Name.setCharacterSize(40);
	player2Name.setFillColor(sf::Color::Yellow);
	player2Name.setPosition(sf::Vector2f(200.0f, 450.0f));

	player2Score.setFont(font);
	player2Score.setString(score2);
	player2Score.setCharacterSize(40);
	player2Score.setFillColor(sf::Color::Yellow);
	player2Score.setPosition(sf::Vector2f(700.0f, 450.0f));

	player3Name.setFont(font);
	player3Name.setString(name3);
	player3Name.setCharacterSize(40);
	player3Name.setFillColor(sf::Color::Blue);
	player3Name.setPosition(sf::Vector2f(200.0f, 600.0f));

	player3Score.setFont(font);
	player3Score.setString(score3);
	player3Score.setCharacterSize(40);
	player3Score.setFillColor(sf::Color::Blue);
	player3Score.setPosition(sf::Vector2f(700.0f, 600.0f));

	while (window.isOpen()) {

		sf::Event Event;

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

				case sf::Event::Closed:
					window.close();
					return 0;
				case sf::Event::MouseButtonPressed:
				{
					float mouseX = sf::Mouse::getPosition(window).x;
					float mouseY = sf::Mouse::getPosition(window).y;

					float btnPosX0 = 440;
					float btnPosY0 = 760;

					float btnxPosWidth0 = 530;
					float btnyPosHeight0 = 860;

					if (mouseX<btnxPosWidth0 && mouseX>btnPosX0 && mouseY<btnyPosHeight0 && mouseY>btnPosY0)
					{
						return 0;
					}
				}
			}
		}
		this->draw(window);
	}
}

void HighScore::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(80, 240, 180));
	window.draw(logoSprite);
	window.draw(backSprite);
	window.draw(player1Name);
	window.draw(player2Name);
	window.draw(player3Name);
	window.draw(player1Score);
	window.draw(player2Score);
	window.draw(player3Score);
	window.display();

}