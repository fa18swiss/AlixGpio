#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>


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
            printf("Here is the message: %s\n",buffer);
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







