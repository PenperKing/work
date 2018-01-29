#include "main.h"
#include "do_user_task.h"

unsigned char do_ADD_AN_ACCOUNT_task(int msgid_cmd, int msgid_user)
{
	Msguser_t Msguser = {};
	Msgcmd_t  Msgcmd = {};
  int fd;//id.dat文件描述符，User.dat文件描述符
	int idat_size;//id.dat 文件大小
	int now_id;
	char user_fd_name[20];//用户信息文件名称
	int wr_cnt;//写字节返回字节数
	
	fd = open("id.dat", O_CREAT | O_RDWR, 0660);
	if (fd == -1)
	{
		perror("open");
		exit(-1);
	}
	idat_size = lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET);
	if (idat_size == 0)//如果idat文件为空
	{
		now_id = 0;
		lseek(fd, 0, SEEK_SET);
		write(fd, &now_id, sizeof(now_id));
	}
	lseek(fd, 0, SEEK_SET);
	read(fd, &now_id, sizeof(now_id));
	printf("iddat_size = %d, now_id = %d\n", idat_size, now_id);
	//读取用户信息
	if(msgrcv(msgid_user, &Msguser, sizeof(User_t), USER_MSG, 0) == -1)
	{
		perror("msgrcv");
		exit(-1);
	}
	Msguser.user_s.ID = now_id + 1;
	Msguser.user_s.sal = 0;
	lseek(fd, 0, SEEK_SET);
	write(fd, &(Msguser.user_s.ID), sizeof(Msguser.user_s.ID));
	printf("seriver get dat!!!name is %s,passwd = %s,ID = %d,sal = %f\n",\
			Msguser.user_s.name, Msguser.user_s.passwd,Msguser.user_s.ID,Msguser.user_s.sal);
	close(fd);
	//保存用户信息
	if (chdir("USER_Information") == -1)
	{
		if ( mkdir ("USER_Information", 0770) == -1)
		{
			perror("mkdir");
			exit(-1);
		}
		if (chdir("USER_Information") == -1)
		{
			perror("chdir");
			exit(-1);
		}
	}
	sprintf(user_fd_name,"%s.dat",Msguser.user_s.name);
	fd = open(user_fd_name, O_CREAT | O_WRONLY, 0660);
	if (fd == -1)
	{
		perror("open");
		exit(-1);
	}
	lseek(fd, 0, SEEK_SET);
    wr_cnt = write(fd, &Msguser, sizeof(Msguser));
#ifdef debug
	printf("wr_cnt = %d,Msgsize = %d\n", wr_cnt, sizeof(Msguser));
#endif
	close(fd);
	if (chdir("../") == -1)//返回工作目录等待用户输入命令
	{
		perror("chdir");
		exit(-1);
	}
	//返回写入成功或失败
	unsigned char ret = (wr_cnt == sizeof(Msguser))?1:0;
	return ret;
}

unsigned char do_DEL_A__ACCOUNT_task(int msgid_cmd, int msgid_user)
{
	Msguser_t Msguser = {};
	Msgcmd_t  Msgcmd = {};
	
	
}
unsigned char do_DEPOSIT_task(int msgid_cmd, int msgid_user)
{

}
unsigned char do_DRAW_MONEY_task(int msgid_cmd, int msgid_user)
{
	
}
unsigned char do_LONKUP_task(int msgid_cmd, int msgid_user)
{
	
}
unsigned char do_TRANS_ACCOUNT_task(int msgid_cmd, int msgid_user)
{
	
}