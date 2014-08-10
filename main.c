#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/time.h>
#include<pthread.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<time.h>
#include "SerialPort.h"


pthread_t thread[1];
pthread_mutex_t mut;
int fd =0;
int IsReceve = 0;
unsigned char msg[1024];

time_t now;
struct tm *tm_now;
char *datetime;

void read_port(void)
{
	fd_set rd;
	int nread,retval;

	struct timeval timeout;
	FD_ZERO(&rd);
	FD_SET(fd,&rd);
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	while(IsReceve == 1);
	retval = select(fd+1,&rd,NULL,NULL,&timeout);
	switch(retval)
	{
	case 0:
		//printf("No data input within 1 seconds.\n");
		break;
	case -1:
		perror("select:");
		break;
	default:
		if( (nread = read(fd,msg,1024))>0 )
		{
			IsReceve =1;
			//printf("%sReceiveMessage: %s\n",msg,datetime);
			printf("\n%sReceive %d bytes,Message is:\n%s\n",datetime,nread,msg);
			
			memset(msg,0,1024);
		}
		break;		
	}//end of switch

}

void *recv_thread()
{
	read_port();
	pthread_exit(NULL);
}



void create_thread(void)
{
	int temp;
	memset(thread,0,sizeof(thread));
	if((temp = pthread_create(&thread[0],NULL,(void *)read_port,NULL)) != 0)
		printf("Create recv_thread failed!\n");
	
}

void wait_thread(void)
{

	if(thread[0] != 0)
	{
		pthread_join(thread[0],NULL);
		//printf("recev_thread end\n");

	}
}


int main()
{
	maintest();	
}

/*

int main()
{
	//int fd = 0;
	char buffer[BUFFER_SIEZE] = {0};

	if((fd = Open_Port(HOST_PORT)) == -1)
	{
		perror("Open port");
		return -1;
	}
	
	if( Set_Port(fd,9600,8,'N',1) == -1)
	{
		perror("Set_Port");
		return -1;
	}
	
	//Serial_SendStr(fd,"Hello This is from Ubuntu\n");

	pthread_mutex_init(&mut,NULL);
	
	while(1)
	{
		time(&now);
		tm_now = localtime(&now);
		datetime=asctime(tm_now);
		
		create_thread();
        wait_thread();
		if( IsReceve ==1)
        {
	        printf("\n%sInput the Send Message:\n",datetime);
       memset(buffer,0,BUFFER_SIEZE);
        if(fgets(buffer,BUFFER_SIEZE,stdin) == NULL)
        {
			perror("Fgets");
			break;
		}
		write(fd,buffer,strlen(buffer));		
			IsReceve = 0;
			
		}
        

	}
	
	close(fd);
	
	return 0;
 
}

*/
