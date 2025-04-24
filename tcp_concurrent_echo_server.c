#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

main(int argc,char*argv[])
{
	int sid,sid1,rval,itr,i,pid;// sid is half association. sid1 is full association
	struct sockaddr_in s,c;
	char buffer[20];
	int clen; //accept() uses value-result parameter
	system("clear");
	if(argc<3)
	{	
		printf("\nUSAGE : %s IP_ADDRESS PORT#\n",argv[0]);
		exit(0);
	}
	printf("\nEnter the number of clients to serve/ server iterations : ");
	scanf("%d",&itr);
	sid=socket(AF_INET,SOCK_STREAM,0);
	if(sid==-1)
	{
		perror("SOCK-CRE-ERR:");
		exit(1);
	}
	/*DEFINING NAME OF THE SERVICE*/
	s.sin_family=AF_INET;
	s.sin_addr.s_addr=inet_addr(argv[1]);
  s.sin_port=htons(atoi(argv[2]));
	/*BIND SOCKET- indicates the process that is listening*/
	rval=bind(sid,(struct sockaddr*)&s,sizeof(s));
	if(rval==-1)
	{
		perror("BIND-ERR:");
		close(sid);
		exit(1);
	}
	rval=listen(sid,5);//range : 1-5
	if(rval==-1)
	{
		perror("LISTEN-ERR:");
		close(sid);
		exit(1);
	}
	for(i=1;i<=itr;i++)
	{
		clen=sizeof(c);
		sid1=accept(sid,(struct sockaddr*)&c,&clen);
		if(sid1==-1)
		{	
			perror("ACCEPT-ERR:");
			close(sid);
			exit(1);
		}
		pid=fork();
		if(pid==-1)
		{
			perror("FRK-ERR:");
			close(sid1);
			close(sid);
			exit(1);
		}
    /*sid1 is a full association tuple and has information of client,server and communication protocol i.e serving socket*/
		if(pid==0) //CHILD
		{
			rval=recv(sid1,buffer,sizeof(buffer),0);
			if(rval==-1)
			{
				perror("MSG-RCV-ERR:");
			}
			else
			{
				printf("\nClient request is %s\n",buffer);
			}
			rval=send(sid1,buffer,sizeof(buffer),0);
			if(rval==-1)
			{	
				perror("MSG-SND-ERR:");
			}
			else
			{
				printf("\nResponse sent\n");
			}
			close(sid1);//closing the serving socket
			exit(0);
		}
		else  //PARENT
			close(sid1);/*parent also has a copy of the serving socket. So close it here.*/
	}
	close(sid);//closing the listening socket
	exit(0);
}
