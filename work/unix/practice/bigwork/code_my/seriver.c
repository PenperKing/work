#include "main.h"
#include "do_user_task.h"

void protacol_cilient_cmd(int msgid_cmd, int msgid_user);
void quit(int signo);

int main(void)
{
	key_t key_cmd = ftok (".", 222);
	key_t key_user = ftok (".", 223);
	signal(SIGINT, quit);
	if (key_cmd == -1 | key_user == -1)
	{
		perror("ftok");
		exit(-1);
	}
	int msgid_cmd  = msgget(key_cmd, 0666|IPC_CREAT);
	int msgid_user = msgget(key_user, 0666|IPC_CREAT);
	if (msgid_cmd == -1 | msgid_user == -1)
	{
		perror("msgget");
		exit(-1);
	}
	protacol_cilient_cmd(msgid_cmd,msgid_user);
}
void protacol_cilient_cmd(int msgid_cmd, int msgid_user)
{
	Msgcmd_t  msgcmd = {};	
	msgcmd.type = CMD_MSG;
	while(1)
	{
		unsigned char  ret = 0;
		if (msgrcv(msgid_cmd, &msgcmd, sizeof(Opt_t), CMD_MSG, 0) == -1)
		{
			perror("msgid_cmd");
			exit(-1);
		}
		switch (msgcmd.cmd)
		{
			case ADD_AN_ACCOUNT:ret = do_ADD_AN_ACCOUNT_task(msgid_cmd,msgid_user);break;
			case DEL_A__ACCOUNT:ret = do_DEL_A__ACCOUNT_task(msgid_cmd,msgid_user);break;
			case DEPOSIT			 :ret = do_DEPOSIT_task(msgid_cmd,msgid_user); break;
			case DRAW_MONEY		 :ret = do_DRAW_MONEY_task(msgid_cmd,msgid_user);break;
			case LOOKUP				 :ret = do_LONKUP_task(msgid_cmd,msgid_user);break;
			case TRANS_ACCOUNT :ret = do_TRANS_ACCOUNT_task(msgid_cmd,msgid_user);break;
			default: ret = 0;break; 
		}
		
		msgcmd.cmd = ret?OPT_SUCC:OPT_FAILED;
		if (msgsnd (msgid_cmd, &msgcmd, sizeof(msgcmd.cmd), 0) == -1)
	  {
	    perror("msgsnd");
	    exit(-1);
	  }
	}
}

void quit(int signo)
{
	key_t key_cmd = ftok (".", 222);
	key_t key_user = ftok (".", 223);
	int msgid_cmd  = msgget(key_cmd, 0);
	int msgid_user = msgget(key_user, 0);
	msgctl(msgid_cmd,  IPC_RMID, 0);
	msgctl(msgid_user, IPC_RMID, 0);
	exit(0);
}






