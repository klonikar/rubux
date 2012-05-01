/*
 * handle.c
 *
 *  Created on: 13 Mar 2012
 *      Author: gareth
 *
 *      do the coded message handling in here
 */


#include "actions.h"

int handle_command(char * buf) {
	int rc = 0;
	int cmd = -1;
	char *ss  = (char*) malloc(1);

	ss=strndup( buf, 1);		// first part of the command
	cmd = atoi(ss);      		    // make it an int

	printf("listener: packet contains \"%s\"\n", buf);
	printf("cmd = int %i \n", cmd);

	switch (cmd) {
	case MOUSE_MOVE:
		mouse_move(buf);
		break;
	case MOUSE_BUTTON:
		mouse_click(buf);
		break;
	case KEYSTROKE:
		type_char(buf);
		break;

		// TODO: more commands here such as MOUSE_DOWN, MOUSE_UP, KEYDOWN, KEYUP

	default:
		printf("listener: packet contains \"%s\"\n", buf);
		rc = -1;
		break;
	} // switch (cmd)
	return rc;
}

