#include <iostream>
#include <cstdlib>
#include <string>

#include <pthread.h>

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
using std::cerr;
using std::cin;
using std::endl;
using namespace rapidjson;

const int BUFFER_SIZE = 512;

JsonServer * jsonServer;

void* doprocessing (void * param) {
	int sock = (int)param;
	int n, posStart;
	string::size_type posEnd;
	char buffer[BUFFER_SIZE];
	string msg, split;
	bool stop;
	while(true) {
		bzero(buffer,BUFFER_SIZE);

		n = read(sock, buffer, BUFFER_SIZE);
		
		if (n > 0) {
			msg = buffer;
			//cout << "r'" << msg << "'" << endl;
			posStart = 0;
			stop = false;
			do {
				posEnd = msg.find('\n', posStart);
				if (posEnd == string::npos) {
					stop = true;
					posEnd = msg.length();
				} 
				split = msg.substr(posStart, posEnd - posStart);
				if (split.length() > 0) {
					//cout << "r2'" << split << "'" << endl;
					string response = jsonServer->process(split) + "\r\n";
					//cout << "s'" << response << "'" << endl;
					n = write(sock,response.c_str(),response.length());
					if (n < 0) {
						cerr << "ERROR writing to socket" << endl;
						close(sock);
						return 0;
					}
				}
				posStart = posEnd + 1;
			} while (!stop);
		} else if (n < 0) {
			cerr << "ERROR reading from socket" << endl;
			close(sock);
			return 0;
		} else {
			close(sock);
			return 0;
		}		
	}
	return 0;
}	

int main( int argc, char *argv[] )
{
	GpioMpsse gpio;
	TurnoutList list(4);
	ImageReader imageReader("Images/");
	list.set(0, new TurnoutLeft(&gpio, "1", 0, "Same"));
	list.set(1, new TurnoutLeft(&gpio, "2", 1, "Same"));
	list.set(2, new TurnoutRight(&gpio, "3", 2, "Same"));
	list.set(3, new TurnoutRight(&gpio, "4", 3, "Same"));
	list.get(1)->setState(Left);
	list.get(2)->setState(Right);
	jsonServer = new JsonServer(&list, &imageReader);
	
	int sockfd, newsockfd, portno;
	unsigned int clilen;

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
		cerr << "ERROR opening socket" << endl;
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
		cerr << "ERROR on binding" << endl;
		exit(1);
	}

	/* Now start listening for the clients, here
	* process will go in sleep mode and will wait
	* for the incoming connection
	*/
	cout << "Listening to port " << portno << endl;
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	while (true) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
		{
			cerr << "ERROR on accept" << endl;
			exit(1);
		}
		pthread_t thread;
		pthread_create(&thread, NULL,doprocessing, (void*) newsockfd);
	} /* end of while */
	delete jsonServer;
}
