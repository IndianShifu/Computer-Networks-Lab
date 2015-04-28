#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

struct Packet {
    int mInfo;
    int mAck;
    int mType;
}mReceived,Ack;


int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;
    int lastack = -1;
    int to_be_received = 0;
    char in;

    if(argc != 2)
    {
        printf("\nPlease enter the IP Address(0.0.0.0)\n");
        return 1;
    }

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\nCould not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4444);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\nError occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\nConnection Denied\n");
       return 1;
    }

    while (1)
    {

    if((n = read(sockfd, &mReceived, sizeof(mReceived))) < 0)
        break;

    printf("Do you want to receive Packet No. %d?(Y|N)\n",mReceived.mInfo);
    scanf(" %c",&in);

    if(in=='Y'||in=='y') {

        if(mReceived.mInfo != to_be_received)
        {
	    printf("Packet No. %d has been dropped.\n",mReceived.mInfo);
            Ack.mInfo = -1;
            Ack.mType = 3;
            printf("Acknowlegement for the packet no. %d has been sent\n",Ack.mInfo);
            write(sockfd, (void*)&Ack, sizeof(Ack));
        }else {
            printf("Packet no. %d has been sent to Network Layer!\n",mReceived.mInfo);
            lastack = to_be_received;
            Ack.mInfo = to_be_received+1;
            Ack.mType = 1;
            printf("Acknowlegement for the packet no.  %d has been sent\n",Ack.mInfo);
            write(sockfd,(void*)&Ack, sizeof(Ack));
             to_be_received+=1;

            }
        }
    else {
        Ack.mInfo = -1;
        Ack.mType = 3;
	printf("Acknowlegement for the packet no.  %d has been sent\n",Ack.mInfo);
                write(sockfd,(void*)&Ack, sizeof(Ack));
        }

    }

    if(n < 0)
    {
        printf("\n Read error \n");
    }
    return 0;
}
