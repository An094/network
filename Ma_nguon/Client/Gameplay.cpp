#include "Gameplay.h"
#include "Gameover.h"
Gameplay::Gameplay(sf::RenderWindow &window,SOCKET sock,sockaddr_in serverAddr,int point,std::string name)
{
	this->sock = sock;
	this->serverAddr = serverAddr;
	this->point = point;
	this->name = name;
}


Gameplay::~Gameplay()
{
}
int Gameplay::getPoint()
{
	return this->point;
}
void Gameplay::setPoint(int p)
{
	this->point = p;
}
int Gameplay::Run(sf::RenderWindow &window)
{

	char nameChar[50];
	int len = (this->name).size();
	for (int i = 0; i < len; i++)
		nameChar[i] = this->name[i];
	nameChar[len] = 0;

	char startMessage[BUFF_SIZE];
	sprintf(startMessage, "START%s", nameChar);

	int ret = send(this->sock, startMessage, strlen(startMessage), 0);
	if (ret < 0)
	{
		printf("Error send!\n");
	}

	sf::RectangleShape imgQues(sf::Vector2f(350.0f, 350.0f));

	if (!font.loadFromFile("MATURASC.TTF"))
	{
		std::cout << "Error loading file" << std::endl;
	}

	ques.loadFromFile("Image/khungcauhoi.png");



	question.setTexture(ques);
	question.setPosition(sf::Vector2f(80.0f, 400.0f));
	question.setScale(sf::Vector2f(1.0f, 2.0f));
	question.scale(sf::Vector2f(0.35f, 0.075f));

	nameDisplay.setString("Name: "+this->name);
	nameDisplay.setFont(font);
	nameDisplay.setCharacterSize(40);
	nameDisplay.setPosition(sf::Vector2f(10.0f, 10.0f));
	nameDisplay.setFillColor(sf::Color::Red);
	int select;
	setPoint(-1);
START:
	{
		int ret;
		char buff[BUFF_SIZE];
		ret = recv(this->sock, buff, BUFF_SIZE, 0);
		if (ret < 0)
		{
			printf("Error recv!");
		}
		setPoint(this->getPoint() + 1);
		char header[6];
		for (int i = 0; i < 5; i++)
		{
			header[i] = buff[i];
		}
		header[5] = 0;

		char id[BUFF_SIZE];
		char quesText[BUFF_SIZE];
		char ansAText[BUFF_SIZE];
		char ansBText[BUFF_SIZE];
		char ansCText[BUFF_SIZE];
		char ansDText[BUFF_SIZE];
		ZeroMemory(quesText, sizeof(quesText));
		ZeroMemory(ansAText, sizeof(ansAText));
		ZeroMemory(ansBText, sizeof(ansBText));
		ZeroMemory(ansCText, sizeof(ansCText));
		ZeroMemory(ansDText, sizeof(ansDText));
		int post = 0, a = 0, b = 0, c = 0, d = 0, e = 0,idex=0;
		
		if (strcmp(header, "POINT") == 0)
		{
			int pointFin;
			if (buff[6] != 0)
			{
				pointFin = (buff[5]-48)*10+(buff[6]-48);
			}
			else pointFin = buff[5] - 48;
			printf("Ban that bai diem cua ban: %d ", pointFin);
			Gameover gameover(window, this->sock,this->serverAddr, pointFin,name);
			gameover.Run(window);
		}
		else if (strcmp(header, "QUEST") == 0)
		{
			for (int i = 5; i < ret; i++)
			{
				if (buff[i] == '|') post++;
				else if (post == 0)
				{
					id[idex++] = buff[i];
				}
				else if (post == 1)
				{
					quesText[a++] = buff[i];
				}
				else if (post == 2)
				{
					ansAText[b++] = buff[i];
				}
				else if (post == 3)
				{
					ansBText[c++] = buff[i];
				}
				else if (post == 4)
				{
					ansCText[d++] = buff[i];
				}
				else if (post == 5)
				{
					ansDText[e++] = buff[i];
				}
			}
			int indexQues;
			if (idex == 2)  indexQues = (id[0] - 48) * 10 + (id[1] - 48);
			else if (idex == 1) indexQues = (id[0] - 48);

			printf("\nid: %d",indexQues); 
			printf("Cau hoi: "); puts(quesText);
			printf("Dap an A: "); puts(ansAText);
			printf("Dap an B: "); puts(ansBText);
			printf("Dap an C: "); puts(ansCText);
			printf("Dap an D: "); puts(ansDText);



			imgQues.setPosition(350.0f, 50.0f);
			std::string fileImg = "cauhoi/" + std::to_string(indexQues+1) + ".jpg";
			imageTexture.loadFromFile(fileImg);

			imgQues.setTexture(&imageTexture);

			
			

			std::string text(quesText);
			int numberChar = text.size();
			sf::Vector2f pos;
			pos.x = 500.0f - numberChar / 2 * 20.0f;
			pos.y = 430.f;
			
			textQues.setFont(font);
			textQues.setString(text);
			textQues.setPosition(pos);
			textQues.setCharacterSize(40);
			textQues.setFillColor(sf::Color::White);

		
			std::string pointText = "Point: " + std::to_string(this->getPoint());
			pointDisplay.setFont(font);
			pointDisplay.setString(pointText);
			pointDisplay.setPosition(sf::Vector2f(800.0f, 10.0f));
			pointDisplay.setCharacterSize(40);
			pointDisplay.setFillColor(sf::Color::Red);

			textA.setFont(font);
			std::string ansA(ansAText);
			textA.setString(ansA);
			textA.setPosition(sf::Vector2f(290.0f-(b/2)*20.0f, 570.0f));
			textA.setCharacterSize(40);
			textA.setFillColor(sf::Color::White);

			textB.setFont(font);
			std::string ansB(ansBText);
			textB.setString(ansB);
			textB.setPosition(sf::Vector2f(690.0f - (b / 2)*20.0f, 570.0f));
			textB.setCharacterSize(40);
			textB.setFillColor(sf::Color::White);

			textC.setFont(font);
			std::string ansC(ansCText);
			textC.setString(ansC);
			textC.setPosition(sf::Vector2f(290.0f - (b / 2)*20.0f, 720.0f));
			textC.setCharacterSize(40);
			textC.setFillColor(sf::Color::White);

			textD.setFont(font);
			std::string ansD(ansDText);
			textD.setString(ansD);
			textD.setPosition(sf::Vector2f(690.0f - (b / 2)*20.0f, 720.0f));
			textD.setCharacterSize(40);
			textD.setFillColor(sf::Color::White);

			if (!Button.loadFromFile("Image/button.png"))
				std::cout << "Can't find the image" << std::endl;
			ButtonImageA.setTexture(Button);
			ButtonImageA.setPosition(sf::Vector2f(150.0f, 500.0f));
			ButtonImageA.setScale(sf::Vector2f(1.0f, 2.0f));
			ButtonImageA.scale(sf::Vector2f(0.3f, 0.1f));

			ButtonImageB.setTexture(Button);
			ButtonImageB.setPosition(sf::Vector2f(550.0f, 500.0f));
			ButtonImageB.setScale(sf::Vector2f(1.0f, 2.0f));
			ButtonImageB.scale(sf::Vector2f(0.3f, 0.1f));

			ButtonImageC.setTexture(Button);
			ButtonImageC.setPosition(sf::Vector2f(150.0f, 650.0f));
			ButtonImageC.setScale(sf::Vector2f(1.0f, 2.0f));
			ButtonImageC.scale(sf::Vector2f(0.3f, 0.1f));

			ButtonImageD.setTexture(Button);
			ButtonImageD.setPosition(sf::Vector2f(550.0f, 650.0f));
			ButtonImageD.setScale(sf::Vector2f(1.0f, 2.0f));
			ButtonImageD.scale(sf::Vector2f(0.3f, 0.1f));





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

							float btnPosXA = 160;
							float btnPosYA = 570;

							float btnPosXB = 560;
							float btnPosYB = 570;

							float btnPosXC = 160;
							float btnPosYC = 720;

							float btnPosXD = 560;
							float btnPosYD = 720;

							float btnxPosWidthA = 450;
							float btnyPosHeightA = 640;

							float btnxPosWidthB = 845;
							float btnyPosHeightB = 640;

							float btnxPosWidthC = 450;
							float btnyPosHeightC = 790;

							float btnxPosWidthD = 845;
							float btnyPosHeightD = 790;

							if (mouseX<btnxPosWidthA && mouseX>btnPosXA && mouseY<btnyPosHeightA && mouseY>btnPosYA)
							{
								ButtonImageA.setColor(sf::Color(250, 20, 20));
								textA.setFillColor(sf::Color::Yellow);
								break;
							}
							else
							{
								ButtonImageA.setColor(sf::Color(255, 255, 255));
								textA.setFillColor(sf::Color::White);
							}
							if (mouseX<btnxPosWidthB && mouseX>btnPosXB && mouseY<btnyPosHeightB && mouseY>btnPosYB)
							{
								ButtonImageB.setColor(sf::Color(250, 20, 20));
								textB.setFillColor(sf::Color::Yellow);
								break;
							}
							else
							{
								ButtonImageB.setColor(sf::Color(255, 255, 255));
								textB.setFillColor(sf::Color::White);
							}
							if (mouseX<btnxPosWidthC && mouseX>btnPosXC && mouseY<btnyPosHeightC && mouseY>btnPosYC)
							{
								ButtonImageC.setColor(sf::Color(250, 20, 20));
								textC.setFillColor(sf::Color::Yellow);
								break;
							}
							else
							{
								ButtonImageC.setColor(sf::Color(255, 255, 255));
								textC.setFillColor(sf::Color::White);
							}
							if (mouseX<btnxPosWidthD && mouseX>btnPosXD && mouseY<btnyPosHeightD && mouseY>btnPosYD)
							{
								ButtonImageD.setColor(sf::Color(250, 20, 20));
								textD.setFillColor(sf::Color::Yellow);
								break;
							}
							else
							{
								ButtonImageD.setColor(sf::Color(255, 255, 255));
								textD.setFillColor(sf::Color::White);
							}

						


						}
						break;
						case sf::Event::MouseButtonPressed:
						{
							float mouseX = sf::Mouse::getPosition(window).x;
							float mouseY = sf::Mouse::getPosition(window).y;

							float btnPosXA = 160;
							float btnPosYA = 570;

							float btnPosXB = 560;
							float btnPosYB = 570;

							float btnPosXC = 160;
							float btnPosYC = 720;

							float btnPosXD = 560;
							float btnPosYD = 720;

							float btnxPosWidthA = 450;
							float btnyPosHeightA = 640;

							float btnxPosWidthB = 845;
							float btnyPosHeightB = 640;

							float btnxPosWidthC = 450;
							float btnyPosHeightC = 790;

							float btnxPosWidthD = 845;
							float btnyPosHeightD = 790;

							if (mouseX<btnxPosWidthA && mouseX>btnPosXA && mouseY<btnyPosHeightA && mouseY>btnPosYA)
							{
								select = 1;
								std::cout << "A!" << std::endl;
								printf("Lua chon cua ban: ");
								char ans[7];
								sprintf(ans, "ANS  %d", select);
								ans[6] = 0;
								ret = send(this->sock, ans, 7, 0);
								if (ret < 0)
								{
									printf("Error!");
								}
								else
								{
									goto START;
								}
							}

							if (mouseX<btnxPosWidthB && mouseX>btnPosXB && mouseY<btnyPosHeightB && mouseY>btnPosYB)
							{
								select = 2;
								std::cout << "B!" << std::endl;
								printf("Lua chon cua ban: ");
								char ans[7];
								sprintf(ans, "ANS  %d", select);
								ans[6] = 0;
								ret = send(this->sock, ans, 7, 0);
								if (ret < 0)
								{
									printf("Error!");
								}
								else
								{
									goto START;
								}
							}

							if (mouseX<btnxPosWidthC && mouseX>btnPosXC && mouseY<btnyPosHeightC && mouseY>btnPosYC)
							{
								select = 3;
								std::cout << "C!" << std::endl;
								printf("Lua chon cua ban: ");
								char ans[7];
								sprintf(ans, "ANS  %d", select);
								ans[6] = 0;
								ret = send(this->sock, ans, 7, 0);
								if (ret < 0)
								{
									printf("Error!");
								}
								else
								{
									goto START;
								}
							}

							if (mouseX<btnxPosWidthD && mouseX>btnPosXD && mouseY<btnyPosHeightD && mouseY>btnPosYD)
							{
								select = 4;
								std::cout << "D!" << std::endl;
								printf("Lua chon cua ban: ");
								char ans[7];
								sprintf(ans, "ANS  %d", select);
								ans[6] = 0;
								ret = send(this->sock, ans, 7, 0);
								if (ret < 0)
								{
									printf("Error!");
								}
								else
								{
									goto START;
								}
							}

							
						
						}
						break;
					}

				}


				window.clear(sf::Color(80, 240, 180));


				window.draw(imgQues);
				window.draw(question);
				window.draw(nameDisplay);
				window.draw(pointDisplay);
				window.draw(ButtonImageA);
				window.draw(ButtonImageB);
				window.draw(ButtonImageC);
				window.draw(ButtonImageD);
				window.draw(textQues);
				window.draw(textA);
				window.draw(textB);
				window.draw(textC);
				window.draw(textD);
				window.display();

			}
		}
		
		
	}
}