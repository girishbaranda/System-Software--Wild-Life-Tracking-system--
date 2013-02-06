/* client process */ 
#include <stdio.h>
#include <ctype.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h> 
#define SIZE sizeof(struct sockaddr_in)

struct
{
  int id,place,temp,hum;
	int speed,light,time;
}cli;
 
size_t size=sizeof(cli);
int main(void) 
{ 
int sockfd; 
char c, rc;
printf("enter the place\n");
scanf("%d",&cli.place);
printf("enter the temperature\n");
scanf("%d",&cli.temp);
printf("enter the humidity\n");
scanf("%d",&cli.hum);
printf("enter the speed\n");
scanf("%d",&cli.speed);
printf("enter the light\n");
scanf("%d",&cli.light);
printf("enter the time\n");
scanf("%d",&cli.time);
cli.id=1;
struct sockaddr_in server = {AF_INET, 7000}; 
/* convert and store the server's IP address 
Replace IP address given below*/ 
server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
/* set up the transport end point */ 
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
{ 
	perror("socket call failed"); 
	exit(1); 
} 
/* connect the socket to the server's address */ 
if ( connect (sockfd, (struct sockaddr *)&server, SIZE) == -1) 
{ 
	perror("connect call failed"); 
	exit(1); 
} 
/* send and receive information with the server */ 
printf("client sending data");
wait(20);
send(sockfd,&cli,size,0);
} 


