#ifndef __do_user_task
#define __do_user_task

unsigned char do_ADD_AN_ACCOUNT_task(int msgid_cmd, int msgid_user);
unsigned char do_DEL_A__ACCOUNT_task(int msgid_cmd, int msgid_user);
unsigned char do_DEPOSIT_task(int msgid_cmd, int msgid_user);
unsigned char do_DRAW_MONEY_task(int msgid_cmd, int msgid_user);
unsigned char do_LONKUP_task(int msgid_cmd, int msgid_user);
unsigned char do_TRANS_ACCOUNT_task(int msgid_cmd, int msgid_user);

#endif
