#include "main.h"
#include "do_user_cmd.h"

void do_ADD_AN_ACCOUNT_cmd(int msgid_cmd, int msgid_user)
{
	Msguser_t Msguser = {};
	Msgcmd_t  Msgcmd = {};
	Msguser.type = USER_MSG;
	Msgcmd.type  = CMD_MSG;
	
	Msgcmd.cmd = ADD_AN_ACCOUNT;
	printf("Your name is :");
	OPEN_CURSOR();
	scanf("%s", Msguser.user_s.name);
 again:NULL;
	char passwd_once[6],passwd_again[6];
	strcpy(passwd_once, getpass("Please input your account passwd(must equcle to six chars)\n")); 	
	OPEN_CURSOR();
	strcpy(passwd_again, getpass("Please reinput your account passwd to confirm it\n"));
	OPEN_CURSOR();

	if (strcmp(passwd_once,passwd_again) == 0 && strlen(passwd_once) == 6)
	{
		puts("Creat accout succfule");
		strcpy(Msguser.user_s.passwd, passwd_again);
		printf("your name is %s, passwd = %s\n", Msguser.user_s.name, Msguser.user_s.passwd);
		int cmdsnd_cnt = msgsnd (msgid_cmd, &Msgcmd, sizeof(Msgcmd.cmd), 0);
		if (cmdsnd_cnt == -1)
		{
			perror("msgcmd");
			exit(-1);
		}
		int usersnd_cnt = msgsnd (msgid_user, &Msguser, sizeof(Msguser.user_s), 0);
		if (cmdsnd_cnt == -1)
		{
			perror("msgcmd");
			exit(-1);
		}
		int cmdrcv_cnt = msgrcv (msgid_cmd, &Msgcmd, sizeof(Msgcmd.cmd), CMD_MSG, 0);
		if (cmdsnd_cnt == -1)
		{
			perror("msgcmd");
			exit(-1);
		}
		if (Msgcmd.cmd == OPT_FAILED)
		{
			puts("Creat failed");
		}
		if (Msgcmd.cmd == OPT_SUCC)
		{
			puts("Creat succ");
		}
	}
	else 
	{
		static char input_cnt = 0;
		input_cnt++;
		puts("the passwd is not match the former passwd,pleass reinput your passwd again");
		if (input_cnt == 2)
		{
			puts("Sorry, i am brain water,next time if i tell the passwd does not match,\
					Please restart the me(stubid machine) again ! ");
		}
		if (input_cnt == 3)
		{
			puts("please restart me again!");
			exit(0);
		}
		goto again;
	}
}	

void do_DEL_A__ACCOUNT_cmd(int msgid_cmd, int msgid_user)
{
	Msgcmd_t msgcmd; 
	msgcmd.type = CMD_MSG;
	msgcmd.cmd  = DEL_A__ACCOUNT;
	if (msgrcv (msgid_cmd, &msgcmd, sizeof(msgcmd.cmd), CMD_MSG, 0) == -1)
	{
		perror("msgrcv");
		exit(-1);
	}
	if (msgcmd.cmd == OPT_SUCC)
	{
		printf("成功删除用户\n");
	}
	
	if (msgcmd.cmd == OPT_FAILED)
	{
		printf("未能成功删除用户\n");
	}
}
void do_DEPOSIT_cmd(int msgid_cmd, int msgid_user)
{
	int fd ;

}
void do_DRAW_MONEY_cmd(int msgid_cmd, int msgid_user)
{
	
}
void do_LONKUP_cmd(int msgid_cmd, int msgid_user)
{
	
}
void do_TRANS_ACCOUNT_cmd(int msgid_cmd, int msgid_user)
{
	
}
