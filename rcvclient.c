/* client process */ 
#include <ctype.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h> 
#include <stdio.h>
#define SIZE sizeof(struct sockaddr_in)
struct recvclient
{
  int place,temp,hum,speed,light,time;
}rcvcli;


struct reqclient
{
	int request,amt,place;
}reqcli; 

size_t sizet=sizeof(rcvcli);
size_t size=sizeof(reqcli);

int option;

int main(void) 
{ 
	int sockfd; 
	char c, rc; 
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

	while(1)
	{
		int a=0;
		printf("\nMenu\n");
		printf("1. Get the specific record\n");
		printf("2. Delete the specific record\n");
		printf("3. Exit\n");
		printf("\nEnter  your option");
		scanf("%d",&option);
		switch(option)
		{
			case 1:
				printf("\nEnter the place whose data you want:");
				scanf("%d",&reqcli.place);
				printf("\nEnter the amount of recent data you want:");
				scanf("%d",&reqcli.amt);
				reqcli.request=2;
				printf("\nrequest client is sending data %d",reqcli.request);
				a=send(sockfd,&reqcli,size,0);
				printf("\n Sending data:%d!!!",a);
				break;
			
			case 2:
				
				printf("\nEnter the place whose data you want to delete:");
				scanf("%d",&reqcli.place);
				printf("\nEnter the amount of recent data you want to delete:");
				scanf("%d",&reqcli.amt);
				reqcli.request=1;
				send(sockfd,&reqcli,size,0);
				printf("\nThe data has been successfully deleted from the file!!");
				break;
			case 3:
				printf("\nClient exiting. Have a nice day");
				exit(0);
			default:
				printf("option not valid. Enter valid option!!!");
				break;
		}
					
	}
} 

