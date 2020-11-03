#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/syscall.h>

/*
 *ты самый лучший*
 */

unsigned char* getstring(unsigned int* len)
{
	*len=0;
	unsigned capacity=1;
	unsigned char* s=(unsigned char*)malloc(10*sizeof(unsigned char));
	unsigned char c=getchar();
	
	while(c!='\n')
	{
		s[(*len)++]=c;
		if(*len>=10)
		{
			capacity*=2;
			s=(unsigned char*)realloc(s, capacity*sizeof(unsigned char));
		}
		c=getchar();
		//printf("%c",c);
	}
	s[*len]='\0';
	return s;
}

struct _MSG
{
	long mtype;
	unsigned action;
	unsigned char mtext[255];
	pid_t newuserPID;
} MSG;

struct _USERS
{
	unsigned char UserName[255];
	pid_t UserPID;
} USERS[10];

struct _UsersMSG
{
	long mtype;
	unsigned char mtext[255];
} UsersMSG;

struct _UserMSGSND
{
	long mtype;
	unsigned char mtext[255];
} UsersMSGSND;

unsigned char NameOfUsers[10][1024];



int main(void)
{
	MSG.mtype=1L;
	key_t mainkey=(unsigned)6666;
	int msgid=msgget(mainkey, 0666|IPC_CREAT);
	//mainkey=6666;
	//msgid=msgget(mainkey, 0666|IPC_CREAT);
	struct msqid_ds buff;
	int rc=0;
	//**************************************************************//
	memset(NameOfUsers, 0, sizeof(NameOfUsers));
	for(unsigned f=0; f<10; f++)
		printf("%s\n", NameOfUsers[f]);
	//*************************************************************//


	memset(USERS, 0, sizeof(USERS));
	key_t UsersRecvKey=1010;
	int usersmsgid=msgget(UsersRecvKey, 0666|IPC_CREAT);
	struct msqid_ds UsersBuff;

	while(1)
	{
		if(rc=msgctl(msgid, IPC_STAT, &buff)<0)
			perror("MSGCTL");
		/*
		else
			perror("MSGCTL");
		printf("CTL_LOG: msg_qnum=%u\n", (unsigned)buff.msg_qnum);
		*/
		if((unsigned)buff.msg_qnum>0)
		{
			if((msgrcv(msgid, &MSG, sizeof(MSG), 1L, 0))<0)
			{
				perror("MSGRCV");
			}
			else
			{
				perror("MSGRCV");
				if(MSG.action==1)
				{
					printf("New user name: %s\nNew user PID: %u\n", MSG.mtext, MSG.newuserPID);
					for(unsigned i=0; i<10; i++)
					{
						if(USERS[i].UserPID==0)
						{
							strcpy(USERS[i].UserName, MSG.mtext);
							USERS[i].UserPID=MSG.newuserPID;
							printf("USERS[%d].UserName:%s\n", i,USERS[i].UserName);
							printf("USERS[%d].UserPID:%d\n", i,USERS[i].UserPID);
							break;
						}
						else
							continue;
					}
				}
				else if(MSG.action!=1)
				{
					printf("Action is remove:%d\n", MSG.action);
					for(unsigned i=0; i<10; i++)
					{
						if(MSG.newuserPID==USERS[i].UserPID)
						{
							/*
							UsersMSGSND.mtype=1L;
							key_t UserSNDKey=(unsigned)USERS[i].UserPID;
							int usersndid=msgget(UserSNDKey, 0666|IPC_CREAT);
							if((msgctl(usersmsgid, IPC_RMID, NULL))<0)
								perror("Users RM_queue");
							else
								perror("Users RM_queue");
							*/
							USERS[i].UserPID=0;
						}
						else
							continue;
					}
				}
			}
		}

		if((msgctl(usersmsgid, IPC_STAT, &UsersBuff))<0)
			perror("Users recv MSGCTL");
		if((unsigned)UsersBuff.msg_qnum>0)
		{
			if((msgrcv(usersmsgid, &UsersMSG, sizeof(UsersMSG), 1L, 0))<0)
				perror("Users MSGRCV");
			else
			{
				perror("Users MSGCRV");
				printf("Users MSG: %s\n", UsersMSG.mtext);
				for(unsigned i=0; i<10; i++)
				{
					if(USERS[i].UserPID!=0)
					{
						UsersMSGSND.mtype=1L;
						key_t UserSNDKey=(unsigned)USERS[i].UserPID;
						int usersndid=msgget(UserSNDKey, 0666|IPC_CREAT);
						strcpy(UsersMSGSND.mtext, UsersMSG.mtext);
						if((msgsnd(usersndid, &UsersMSGSND, sizeof(UsersMSGSND), 0))<0)
							perror("User MSGSND");
						else
						{
							perror("User MSGSND");
							printf("User PID: %d\n", USERS[i].UserPID);
						}
					}
				}
			}
		}

		/*
		for(unsigned i=0; i<10; i++)
		{
			if(USERS[i].UserPID!=0)
			{
				UsersMSG.mtype=1L;
				key_t UserMSGkey=(unsigned)USERS[i].UserPID;
				int UserMsgid=msgget(UserMSGkey, 0666|IPC_CREAT);
				struct msqid_ds UserBuff;
				int UserRC=0;
				
				if((msgctl(UserMsgid, IPC_STAT, &UserBuff))<0)
					perror("User MSGCTL");
				
				if((unsigned)UserBuff.msg_qnum>0)
				{
					//printf("User MSGCTL.msg num:%d\n", (unsigned)UserBuff.msg_qnum);
					if((msgrcv(UserMsgid, &UsersMSG, sizeof(UsersMSG), 1L, 0))<0)
					{
						perror("Users MSGRCV");
					}
					else
					{
						perror("Users MSGRCV");
						printf("Users MSGCTL.msg num:%d\n", (unsigned)UserBuff.msg_qnum);
						printf("Users MSG:%s\n", UsersMSG.mtext);
						if((msgsnd(UserMsgid, &UsersMSG, sizeof(UsersMSG),0))<0)
							perror("Users MSGSND");
						else
							perror("Users MSGSND");
					}
				}
			}
		}
		*/
		/*
		else if((unsigned)buff.msg_qnum==0)
		{
			printf("MSG_NUM:%d\n", (unsigned)buff.msg_qnum);
		}
		*/
		
	}
}
