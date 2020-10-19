#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <conio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <process.h>
#include <ctime>
#include<string.h>
#include<vector>

#define SERVER_PORT 5500
#define BUFF_SIZE 2048
#define MAX_ARRAY 50
#define MAX_HEADER 7
#define MAX 10

#pragma comment(lib,"Ws2_32.lib")
//struct question
typedef struct question {
	char quesText[BUFF_SIZE];
	char firstAns[BUFF_SIZE];
	char secondAns[BUFF_SIZE];
	char thirdAns[BUFF_SIZE];
	char fourthAns[BUFF_SIZE];
	int numberCorrectAns;
}ques;
//struct question
typedef struct highScore{
	char name[BUFF_SIZE];
	char score[BUFF_SIZE];
}hscore;
//struct node contain connsock and userplayer and point
typedef struct {
	SOCKET connSock;
	char userName[BUFF_SIZE];
	int point;
}node;
//init array node  
node sock[MAX];
int num = 0;
//Declare file names available in the package
const char* fileNameScore = "highScore.txt";
const char* fileName = "cauhoi.txt";
//create Node . This is Player 
node createNode(SOCKET connSock, char* userName,int point)
{
	node p;
	p.connSock = connSock;
	strcpy(p.userName, userName);
	p.point = point;
	return p;
}
ques* getQuesFromFile();

hscore* getHighScoreFromFile();


unsigned __stdcall Proccess(void*);
void start(SOCKET,int);
void score(SOCKET);
void updateScoreFile(hscore*);

//char current_account[BUFF_SIZE];
int amountOFAccountInFile;

int main()
{


	//Step 1: Initiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData))
		printf("Version is not supported\n");

	//Step 2: Construct socket	
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error! Cannot bind this address.");
		_getch();
		return 0;
	}

	//Step 4: Listen request from client
	if (listen(listenSock, 10)) {
		printf("Error! Cannot listen.");
		_getch();
		return 0;
	}

	printf("Server started!\n");

	//Step 5: Communicate with client
	sockaddr_in clientAddr;
	//char buff[BUFF_SIZE];
	int  clientAddrLen = sizeof(clientAddr);
	
	SOCKET connSock;

	
	while (true)
	{//accept request
		connSock = accept(listenSock, (sockaddr *)& clientAddr, &clientAddrLen);
		printf("NEW CONNECT\n");
		//strcpy(current_account, "\0");
		sock[num++] = createNode(connSock,"",0);
		_beginthreadex(0, 0, Proccess, (void*)&num, 0, 0);
	}
	
	//Step 5: Close socket
	closesocket(listenSock);

	//Step 6: Terminate Winsock
	WSACleanup();
	
}
//create function get data from file and process data transion list question and answer
ques* getQuesFromFile()
{
	FILE *fp = fopen(fileName, "r");
	//array size
	ques* accQuesFile = (ques*)malloc(MAX_ARRAY * sizeof(ques));
	char lineFile[BUFF_SIZE];
	char quesTextFile[BUFF_SIZE];
	char firstAnsFile[BUFF_SIZE];
	char secondAnsFile[BUFF_SIZE];
	char thirdAnsFile[BUFF_SIZE];
	char fourthAnsFile[BUFF_SIZE];
	int numberCorrectAnsFile;
	int len = 0;
	int countLine = 0;
	//process data
	//get question and answer
	while (!feof(fp))
	{	//readline 
		fgets(lineFile, sizeof(lineFile), fp);
		len = strlen(lineFile);
		if (lineFile[len - 1] == '\n')
			lineFile[len - 1] = '\0';
		int position = 0, a =0, j = 0, k = 0 , l = 0, m = 0;
		for (int i = 0; i < len; i++)
		{
			if (lineFile[i] == '|') position++;

			else if (position == 0)
			{
				quesTextFile[a++] = lineFile[i];
			}
			else if (position == 1)
			{
				firstAnsFile[j++] = lineFile[i];
			}
			else if (position == 2)
			{
				secondAnsFile[k++] = lineFile[i];
			}
			else if (position == 3)
			{
				thirdAnsFile[l++] = lineFile[i];
			}
			else if (position == 4)
			{
				fourthAnsFile[m++] = lineFile[i];
			}
			else if (position == 5)
			{
				numberCorrectAnsFile = lineFile[i] - '0';
				break;
			}
		}
		quesTextFile[a] = 0;
		firstAnsFile[j] = 0;
		secondAnsFile[k] = 0;
		thirdAnsFile[l] = 0;
		fourthAnsFile[m] = 0;

		strcpy(accQuesFile[countLine].quesText, quesTextFile);
		strcpy(accQuesFile[countLine].firstAns, firstAnsFile);
		strcpy(accQuesFile[countLine].secondAns, secondAnsFile);
		strcpy(accQuesFile[countLine].thirdAns, thirdAnsFile);
		strcpy(accQuesFile[countLine].fourthAns, fourthAnsFile);
		accQuesFile[countLine].numberCorrectAns = numberCorrectAnsFile;

		countLine++;

	}
	//number of questions
	amountOFAccountInFile = countLine;
	fclose(fp);
	accQuesFile = (ques*)realloc(accQuesFile, countLine * sizeof(ques));
	return accQuesFile;
}
//get highsorce from file local
hscore* getHighScoreFromFile()
{
	FILE *fp = fopen(fileNameScore, "r");
	//create array dynamic
	hscore* accScoreFile = (hscore*)malloc(3 * sizeof(hscore));
	char lineFile[BUFF_SIZE];
	char name[BUFF_SIZE];
	char score[BUFF_SIZE];
	int len = 0;
	int countLine = 0;
	while (!feof(fp))
	{
		fgets(lineFile, sizeof(lineFile), fp);
		len = strlen(lineFile);
		if (lineFile[len - 1] == '\n')
			lineFile[len - 1] = '\0';
		int position = 0, a = 0, b=0;
		for (int i = 0; i < len; i++)
		{
			if (lineFile[i] == '|') position++;

			else if (position == 0)
			{
				name[a++] = lineFile[i];
			}
			else if (position == 1)
			{
				score[b++] = lineFile[i];
			}
		}
		name[a] = 0;
		score[b] = 0;

		strcpy(accScoreFile[countLine].name, name);
		strcpy(accScoreFile[countLine].score, score);
		

		countLine++;

	}
	fclose(fp);
	return accScoreFile;
}

//function process Player 
void start(SOCKET connSock,int number_socket)
{
	//get question and answer
	ques* quesList = getQuesFromFile();			

	std::vector<int> index;

	while (true)
	{	//random
		srand(time(NULL));
		int id = rand() % amountOFAccountInFile;//
		bool wrong = false;
		//check quesstion and answer had used 
		for (int i = 0; i < index.size(); i++)
			if (id == index[i])
			{
				wrong = true;
			}
		if (wrong == true) continue;
		//push id in dict.
		index.push_back(id);
		char quesMessage[BUFF_SIZE];
		sprintf(quesMessage, "QUEST%d|%s|%s|%s|%s|%s", id,
			quesList[id].quesText,
			quesList[id].firstAns,
			quesList[id].secondAns,
			quesList[id].thirdAns,
			quesList[id].fourthAns);
		//send question and answer to Player
		int ret = send(connSock, quesMessage, sizeof(quesMessage), 0);
		if (ret < 0)
		{
			printf("Send message error!\n");
			break;
		}
		char ansMessage[BUFF_SIZE];
		//receive ans client
		ret = recv(connSock, ansMessage, BUFF_SIZE, 0);
		if (ret < 0)
		{
			printf("Recv message error!\n");
			break;
		}
		ansMessage[ret] = 0;

		char header[6];
		int answer;
		for (int i = 0; i < 5; i++)
			header[i] = ansMessage[i];
		header[5] = 0;
		if (strcmp(header, "ANS  ") == 0) answer = (int)ansMessage[5] - 48;
		if (answer == quesList[id].numberCorrectAns)
		{
			sock[number_socket].point++;
			continue;
		}
		else
		{
			printf("Incorrect! Game over!\n");
			int point = sock[number_socket].point;
			char mess[BUFF_SIZE];
			sprintf(mess, "POINT%d", point);
			ret = send(connSock, mess, sizeof(mess), 0);
			sock[number_socket].point = 0;
			char pointChar[3];
			if (point < 10) {
				pointChar[0] = point + 48;
				pointChar[1] = 0;
			}
			else {
				pointChar[0] = (point / 10) + 48;
				pointChar[1] = (point % 10) + 48;
				pointChar[2] = 0;
			}
			//get highscore
			hscore* highScoreList = getHighScoreFromFile();
			//equal point and highscore
			if (point > atoi(highScoreList[2].score))
			{
				if (point > atoi(highScoreList[1].score))
				{
					if (point > atoi(highScoreList[0].score))
					{
						strcpy(highScoreList[2].name, highScoreList[1].name);
						strcpy(highScoreList[2].score, highScoreList[1].score);
						strcpy(highScoreList[1].name, highScoreList[0].name);
						strcpy(highScoreList[1].score, highScoreList[0].score);
						strcpy(highScoreList[0].name, sock[number_socket].userName);
						strcpy(highScoreList[0].score, pointChar);
					}
					else
					{
						strcpy(highScoreList[2].name, highScoreList[1].name);
						strcpy(highScoreList[2].score, highScoreList[1].score);
						strcpy(highScoreList[1].name, sock[number_socket].userName);
						strcpy(highScoreList[1].score, pointChar);
					}
				}
				else
				{
					strcpy(highScoreList[2].name, sock[number_socket].userName);
					strcpy(highScoreList[2].score, pointChar);
					
				}
			}
			//update
			updateScoreFile(highScoreList);
			return;
		}

	}
}
//function update highScore
void updateScoreFile(hscore* highScoreList)
{
	FILE *fps = fopen(fileNameScore, "w");
	for (int i = 0; i < 3; i++)
	{
		char infor[BUFF_SIZE];
		if(i==2) sprintf(infor, "%s|%s\0", highScoreList[i].name, highScoreList[i].score);
		else sprintf(infor, "%s|%s\n", highScoreList[i].name, highScoreList[i].score);
		fputs(infor, fps);
	}
	fclose(fps);
}

//function get highscore and send Client
void score(SOCKET connSock)
{
	hscore* highScoreList = getHighScoreFromFile();
	char scoreMess[BUFF_SIZE];
	sprintf(scoreMess, "SCORE%s|%s|%s|%s|%s|%s", highScoreList[0].name, 
											highScoreList[0].score, 
											highScoreList[1].name, 
											highScoreList[1].score, 
											highScoreList[2].name, 
											highScoreList[2].score);
	
	int ret = send(connSock, scoreMess, strlen(scoreMess), 0);
	if (ret < 0)
	{
		printf("Error send\n");
		
	}
	return;
}



// processing flow
unsigned __stdcall Proccess(void* param)
{
	int number_socket = *(int*)param - 1;
	node sockNode = sock[number_socket];
	SOCKET connSock = sockNode.connSock;
	char buff[BUFF_SIZE];
	while (true)
	{
		int ret = recv(connSock, buff, BUFF_SIZE, 0);
		if (ret < 0) break;
		buff[ret] = 0;

		char header[6];
		for (int i = 0; i < 5; i++)
			header[i] = buff[i];
		header[5] = 0;
		if (strcmp(header, "START") == 0)
		{
			int a = 0;
			for (int i = 5; i < ret; i++)
				sock[number_socket].userName[a++] = buff[i];
			sock[number_socket].userName[a] = 0;
			//call function start
			start(connSock, number_socket);
		}
		else if (strcmp(header, "SCORE") == 0) score(connSock);
	}
	shutdown(connSock, SD_SEND);
	closesocket(connSock);
	return 0;
}
