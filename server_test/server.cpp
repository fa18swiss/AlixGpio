	#include <iostream>
	#include <cstdlib>
	#include "rapidjson/prettywriter.h" // for stringify JSON
	#include "rapidjson/document.h" // rapidjson's DOM-style API
	#include "rapidjson/prettywriter.h" // for stringify JSON
	#include "rapidjson/filestream.h" // wrapper of C stream for prettywriter as output
	#include <string>
	
	#include "../TurnoutLeft.h"
	#include "../TurnoutList.h"
	#include "../TurnoutRight.h"
	#include "../ImageReader.h"
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
	
	
	void doparse(char* json)
	{
		int size = strlen(json);
	    //const char json[] = " { \"cmd\" : \"list\", \"id\" : \"a\", \"state\" : \"left\" } ";
	    //printf("Original JSON:\n %s\n", json);
	    Document document; // Default template parameter uses UTF8 and MemoryPoolAllocator.
	    printf("size: %d\n", size);
	    char buffer[size];
	    memcpy(buffer, json, size);
	    printf("yolo buffer %s", buffer);
	    if (document.ParseInsitu(buffer).HasParseError())
	    {
			printf("Error while parsing");
	        return;
		}
	    printf("\nParsing to document succeeded.\n");
	
	    printf("\nAccess values in document:\n");
	    assert(document.IsObject()); // Document is a JSON value represents the root of DOM. Root can be either an object or array.
	    char cmd[20];
	    char state[20];
	    char id[20];
	
	    if(document.HasMember("cmd")) {
	        if(document["cmd"].IsString()) {
	            const char* toCopy = document["cmd"].GetString();
	            printf("Has command: %s", toCopy);
	            strcpy(cmd, toCopy);
	        }
	    }
	
	    if(document.HasMember("state")) {
	        if(document["state"].IsString()) {
	            const char* toCopy = document["state"].GetString();
	            printf("Has state: %s", toCopy);
	            strcpy(state, toCopy);
	        }
	    }
	    if(document.HasMember("id")) {
	        if(document["id"].IsString()) {
	            const char* toCopy = document["id"].GetString();
	            printf("Has id: %s", toCopy);
	            strcpy(id, toCopy);
	        }
	    }
	    printf("cmd %s, state %s, id %s", cmd, state, id);
	}
	
	void doprocessing (int sock)
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
	            doparse( buffer );
	            n = write(sock,"I got your message",18);
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
	        doprocessing(newsockfd);
	        close(newsockfd);
	
	    } /* end of while */
	}
	
	
	
	
	
	
	
	
	
