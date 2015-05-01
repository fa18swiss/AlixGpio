#include <iostream>
#include <cstdlib>
#include <string>

#include "TurnoutLeft.h"
#include "TurnoutList.h"
#include "TurnoutRight.h"
#include "ImageReader.h"
#include "JsonServer.h"
#include "GpioMpsse.h"
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

using std::cout;
using std::cin;
using std::endl;
using namespace rapidjson;

void doprocessing (int sock, JsonServer * jsonServer)
{
	int n;
	char buffer[256];
	while(1) {

		bzero(buffer,256);

		n = read(sock,buffer,255);

		if (n < 0)
		{
			printf("ERROR reading from socket");
			return;
		}
		if( n > 0)
		{
			//printf("Here is the message: %s\n",buffer);
				int size = strlen(buffer);
			printf("size outside %d\n", size);
			string msg = buffer;
			cout << "r'"<<msg<<"'"<<endl;
			string response = jsonServer->process(msg) + "\r\n";
			cout << "s'"<<response<<"'"<<endl;
			n = write(sock,response.c_str(),response.length());
		}
		else
		{
			return;
		}
		if (n < 0)
		{
			printf("ERROR writing to socket");
			return;
		}
	}
}	

int main( int argc, char *argv[] )
{
	GpioMpsse gpio;
	TurnoutList list(4);
	ImageReader imageReader("Images/");
	list.set(0, new TurnoutLeft(&gpio, "1", 0, "Same"));
	list.set(1, new TurnoutLeft(&gpio, "2", 1, "Switch"));
	list.set(2, new TurnoutRight(&gpio, "3", 2, "Switch"));
	list.set(3, new TurnoutRight(&gpio, "4", 3, "Same"));
	list.get(1)->setState(Left);
	list.get(2)->setState(Right);
	JsonServer jsonServer(&list, &imageReader);
	
	int sockfd, newsockfd, portno;
	unsigned int clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int  n;
	portno = 9999;

	if (argc >= 2) {
		portno = atoi(argv[1]);
	}

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}

	/* Now start listening for the clients, here
	* process will go in sleep mode and will wait
	* for the incoming connection
	*/
	printf("Listening to port %d.\r\n", portno);
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	while (1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
		{
			printf("ERROR on accept");
			exit(1);
		}
		//close(sockfd);
		doprocessing(newsockfd, &jsonServer);
		close(newsockfd);

	} /* end of while */
}
