#include "main.h"
#include "do_user_cmd.h"

int get_user_cmd(void);
unsigned char do_task_usercmd(Opt_t user_cmd, key_t key_cmd, key_t key_user);
const char logo[]      = "                                     中国银行                                     ";
const char func_logo[] = "【1】 开户 【2】 销户 【3】 存钱 【4】 取钱 【5】 查询 【6】 转账 【7】 退出";

int main(void)
{
	while (1)
	{
		Opt_t user_cmd = (Opt_t)get_user_cmd();
		printf("user_cmd = %d\n", user_cmd);	
		key_t key_cmd = ftok (".", 222);
		key_t key_user = ftok (".", 223);
		if (key_cmd == -1 | key_user == -1)
		{
			perror("ftok");
			exit(-1);
		}
		do_task_usercmd(user_cmd, key_cmd, key_user);
  }
}
unsigned char do_task_usercmd(Opt_t user_cmd, key_t key_cmd, key_t key_user)
{
	int msgid_cmd  = msgget(key_cmd, 0);
	int msgid_user = msgget(key_user, 0);
	if (msgid_cmd == -1 | msgid_user == -1)
	{
		perror("msgget");
		exit(-1);
	}
	switch (user_cmd)
	{
		case ADD_AN_ACCOUNT:do_ADD_AN_ACCOUNT_cmd(msgid_cmd,msgid_user);break;
		case DEL_A__ACCOUNT:do_DEL_A__ACCOUNT_cmd(msgid_cmd,msgid_user);break;
		case DEPOSIT			 :do_DEPOSIT_cmd(msgid_cmd,msgid_user); 			break;
		case DRAW_MONEY		 :do_DRAW_MONEY_cmd(msgid_cmd,msgid_user);		break;
		case LOOKUP				 :do_LONKUP_cmd(msgid_cmd,msgid_user);				break;
		case TRANS_ACCOUNT :do_TRANS_ACCOUNT_cmd(msgid_cmd,msgid_user);	break;	 
		default:break;	
	}
}

int get_user_cmd(void)
{
	int ret = 0;
	printf("\033[1m\033[45;33m %s \033[0m\n", logo);
	puts(func_logo);
	do
	{
		puts("press valid number to choose you want to do! And press ENTER key,to confirm it");
		OPEN_CURSOR();
		scanf("%d", &ret);
		if (ret == 7)
		{
			puts("Wecome to back, my lovely consumer!");
			exit(0);
		}
		if (ret < 1 || ret > 7)
		{
			ret = 0;
		    printf("input error\n");
		}
	}while (ret == 0);
	return ret;
}

