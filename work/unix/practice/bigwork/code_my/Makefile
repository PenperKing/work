#!/bin/bash
OSER:main.h do_user_cmd.h do_user_task.h
	gcc seriver.c do_user_task.c -oOSER
	gcc cilient.c do_user_cmd.c  -oOCI
clean:
	rm -rf OSER OCI *out
aclean:
	rm -rf OSER OCI *out
	rm -rd id.dat USER_Information
