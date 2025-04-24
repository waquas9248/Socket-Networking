#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>
#include<string.h>
main(int argc,char*argv[])
{
	int sid,sid1,rval;// sid is half association. sid1 is full association
	time_t t=time(0);
	struct sockaddr_in s,c;
	char smsg[30];
	strcpy(smsg,ctime(&t));
	int clen; //accept() uses value-result parameter
	system("clear");
	if(argc<3)
	{	
		printf("\nUSAGE : %s IP_ADDRESS PORT#\n",argv[0]);
		exit(0);
	}
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
	clen=sizeof(c);
	sid1=accept(sid,(struct sockaddr*)&c,&clen);
/*sid1 is a full association tuple and has information of client,server and communication protocol i.e serving socket*/
	strcpy(smsg,ctime(&t));//const time_t* if error
	rval=send(sid1,smsg,sizeof(smsg),0);
	if(rval==-1)
	{
		perror("MSG-SND-ERR:");
	}
	else
	{
		printf("\nResponse sent\n");
	}
	close(sid);
	close(sid1);
}

