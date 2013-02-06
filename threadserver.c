/* server process */ 
#include <ctype.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define MAX_CLIENT 50
#define SIZE sizeof(struct sockaddr_in) 

int newsockfd;
 void *handle_client(void *);
int finddataquant(FILE *pptr)
{
  int counter=0;
	char line [ 128 ]; /* or other suitable maximum line size */
	while ( fgets ( line, sizeof line, pptr ) != NULL ) /* read a line */
	{
	counter++;
	}
	return counter;
}

 
int sockfd,req,amount,plce;
int thread_no=0;
pthread_t tid[MAX_CLIENT];


struct 
{
	int request,amt,place;
}ser;

struct sendrequest
{
	int place,temp,hum,speed,light,time;
}sendser;
struct threadstructure{
int myid,mysockfd;},tstruct;

size_t sizet=sizeof(sendser);
size_t size=sizeof(ser);



int main(void) 
{  
char c;


struct sockaddr_in server = {AF_INET, 7000, INADDR_ANY}; 
printf("main");
/* set up the transport end point */ 
if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{ 
	perror("socket call failed"); 
	exit(1); 
	} 
/* bind an address to the end point */ 
if ( bind(sockfd, (struct sockaddr *)&server, SIZE) == -1) 
	{ 
	perror("bind call failed"); 
	exit(1); 
	}
/* start listening for incoming connections */ 
if ( listen(sockfd, MAX_CLIENT ) == -1 ) 
	{ 
	perror("listen call failed"); 
	exit(1) ; 
	} 
	printf("hi mmammam");
while(1)
	{ 
		/* accept a connection */ 
		if ( (newsockfd = accept(sockfd, NULL, NULL)) == -1) 
		{ 
		perror("accept call failed"); 
		continue; 
		} 
	/* spawn a child to deal with the connection */
	        
		thread_no++;
		printf("hi i am entering");
		tstruct.mysockfd=newsockfd;
		tstruct.myid=thread_no;
		sleep(100);
		pthread_create(&tid[thread_no],NULL,handle_client,(void *)&tstruct);
		
	
	}
	
		
		close(newsockfd); 
		exit (0); 
 }


int recvdata(void)
{
printf("%d %d %d %d %d %d\n",sendser.place,sendser.temp,sendser.hum,sendser.speed,sendser.light,sendser.time);
printf("Data received\n");
				if(sendser.place==101)
				{
					write_to_file("101.dat");					
				}
				else if(sendser.place==102)
				{
					write_to_file("102.dat");
				}
				else if(sendser.place==103)
				{
					write_to_file("103.dat");	
				}
				else if(sendser.place==104)
				{
					write_to_file("104.dat");
				}
				else if(sendser.place==105)
				{
					write_to_file("105.dat");
				}
				else
				{
					printf("ERROR client does not exist");
				}
return 0;
}

int requestclient(void)
{
	amount=ser.amt;   // amount will contain the no. of readings requested
	req=ser.request;        // whether request is to delete or retrive the data.
	plce=ser.place;     // plce represent the tracking device  request made for.
	if(req==2)          // req= 0 means retrive  data
	{
		if(plce==101)
		{
		readfromfile("101.dat","temp.dat");
		}
			
		else if(plce==102)
		{
		 readfromfile("102.dat","temp.dat");
		}
					
		else if(plce==103)
		{
		 readfromfile("103.dat","temp.dat");
		}
				
		else if(plce==104)
		{
		 readfromfile("104.dat","temp.dat");
		}
				
		else if(plce==105)
		{
		 readfromfile("105.dat","temp.dat");
		}
		else 
		{
		printf("invalid request");
		}
						
	}
				
   else if(req==1)     // it means delete data
	{
	if(plce==101)
		{
			deletefromfile("101.dat","temp.dat");	
		}
	else if(plce==102)
		{
			deletefromfile("102.dat","temp.dat");
		}
	else if(plce==103)
		{
			deletefromfile("103.dat","temp.dat");
		}
	else if(plce==104)
		{
			deletefromfile("104.dat","temp.dat");
		}
	else if(plce==105)
		{
			deletefromfile("105.dat","temp.dat");
		}
	else
		printf("place requested by main client does not exists");
	}

   else
	{
	printf("invalid request by the main client");
	}
return 0;
}

int write_to_file(char *filename)
{
	FILE *fd;
	fd = fopen(filename,"a");
	fprintf(fd,"%d %d %d %d %d %d\n",sendser.place,sendser.temp,sendser.hum,sendser.speed,sendser.light,sendser.time);
	fclose(fd);
	return 0;
 
}

int readfromfile(char *filename1, char *filename2)
{
	FILE *fptr;
	FILE *ftp;
	int quant,i=0;
	fptr = fopen(filename1,"r");	
	quant=finddataquant(fptr);	//semaphores to be implemented here
	ftp= fopen(filename2,"a");
	fseek(fptr,0,SEEK_SET);
	for(i=1;i<=quant;i++)
	{
		fscanf(fptr,"%d %d %d %d %d %d\n",&sendser.place,&sendser.temp,&sendser.hum,&sendser.speed,&sendser.light,&sendser.time);
								
		if(i>(quant-amount))
		{
		fscanf(fptr,"%d %d %d %d %d %d\n",&sendser.place,&sendser.temp,&sendser.hum,&sendser.speed,&sendser.light,&sendser.time);
		printf("%d %d %d %d %d %d\n",sendser.place,sendser.temp,sendser.hum,sendser.speed,sendser.light,sendser.time);
		send(sockfd,&sendser,sizet,0);
		fprintf(ftp,"%d %d %d %d %d %d\n",sendser.place,sendser.temp,sendser.hum,sendser.speed,sendser.light,sendser.time);
		}

	}
		fclose(fptr);
		fclose(ftp);
return 0;
}

int deletefromfile(char *fname1,char *fname2)
{
	FILE *fptr;
	FILE *ftp;
	int quant,i=0;
	fptr = fopen(fname1,"r");	//semaphores to be implemented here
	quant=finddataquant(fptr);
	ftp= fopen(fname2,"a");
	fseek(fptr,0,SEEK_SET);
	for(i=1;i<=(quant-amount);i++)
	{
	fscanf(fptr,"%d %d %d %d %d %d\n",&sendser.place,&sendser.temp,&sendser.hum,&sendser.speed,&sendser.light,&sendser.time);
	printf("%d %d %d %d %d %d\n",sendser.place,sendser.temp,sendser.hum,sendser.speed,sendser.light,sendser.time);
	fprintf(ftp,"%d %d %d %d %d %d\n",sendser.place,sendser.temp,sendser.hum,sendser.speed,sendser.light,sendser.time);
	}
	remove(fname1);
	rename(fname2,fname1);
	fclose(fptr);
	fclose(ftp);
return 0;
}
 void *handle_client(void *tstruct)
{
		int id,currsockfd;		
		struct threadstructure newstruct;
		newstruct=*((struct threadstructure *)tstruct);
		id=newstruct.myid;
		currsockfd=newstruct.mysockfd;
	
		printf("Thread id is %d",id);
		
		
		if(recv(currsockfd,&sendser,sizet, 0)>20 )
		{
			printf("Thread id is %d",id);
			recvdata();
		}
			
		else if(recv(currsockfd,&ser,size,0))
		{
			printf("Thread id is %d",id);
			printf("\nRequest received");
			requestclient();
		}

		else
			printf("invalid request by the client");			
		
}		
