#ifndef __main_h
#define __main_h

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define CMD_MSG   1
#define USER_MSG  2
#define OPEN_CURSOR() printf("\033[?25h")

typedef enum
{
	OPT_FAILED,
	ADD_AN_ACCOUNT,
	DEL_A__ACCOUNT,
	DEPOSIT,//¥Ê«Æ
	DRAW_MONEY,
	LOOKUP,
	TRANS_ACCOUNT,
	OPT_SUCC,
}Opt_t;

typedef struct 
{
	char name[20];
	double sal;
	char passwd[6];
	unsigned int ID;
}User_t;

typedef struct 
{
	long type;
	Opt_t cmd;
}Msgcmd_t;
typedef struct 
{
	long type;
	User_t user_s;
}Msguser_t;
#endif
