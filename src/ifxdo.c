/*
 * ifxdo.c
 *
 * Interface to xdotool
 *
 * Compile with:
 * gcc -lxdo
 *
 * Requires libxdo (from xdotool project)
 *
 *  Created on: 14 Mar 2012
 *      Author: gareth
 */


#include <xdo.h>

xdo_t * IF_XDO;
unsigned int SCREEN_WIDTH = 0;
unsigned int SCREEN_HEIGHT = 0;


void init_ifxdo() {
	// get the display for the duration of the program
	IF_XDO = xdo_new("");
	// load the screen resolution
	xdo_get_viewport_dimensions(IF_XDO, &SCREEN_WIDTH, &SCREEN_HEIGHT, CURRENTWINDOW);
}


void ifxdo_free() {
	// closing now so free the display
	xdo_free(IF_XDO);
	return;
}


short GetMoveScale(short v, short m) {
	// m is the max range of the screen (full width or height)
	// v is the vector scale as int in 1 to +9
	short a = m;
	short cs = 0;

	v = v - 5;  // offset so 1-9 becomes -4 to +4
	if (v < 0) {
		v = -v;
		cs = 1;
	}

	switch (v) {
	case 4:
		a = (short) m * 0.75;	// max is 3 qtr
		break;
	case 3:
		a = (short) m * 0.5;
		break;
	case 2:
		a = (short) m * 0.25;
		break;
	case 1:
		a = (short) m * 0.05;  // 1 20th of screen dim
		break;
	case 0:
		a = 0;
		break;
	} // switch(v)

	if (cs == 1) {
		a = -a;
	}
	return a;
}


void mouse_move(char * buf) {
	/* Use the command format of 0XY where
	 *  X is the vector for the horizontal mouse move and
	 *  Y is likewise for the vertical mouse pointer shift
	 *  X and Y should always be in the range 1 to 9
	 */
	char *ss = (char*) malloc(1);
	int x, y;

	// convert x to an int which should be in the range 1 to 9
	ss = strndup(buf + 1, 1); // 2nd part of the command is the x axis move
	x = atoi(ss); // make it an int
	ss = strndup(buf + 2, 1); // 3rd part of the command is the y axis move
	y = atoi(ss); // make it an int

	x = GetMoveScale(x, SCREEN_WIDTH);
	y = GetMoveScale(y, SCREEN_HEIGHT);

	printf("move_mouse by %s\n", buf);
	xdo_mousemove_relative(IF_XDO, x, y);
	return;
}


void mouse_click(char * buf) {
	char *ss = (char*) malloc(1);
	int button, repeat;

    // the mouse button. Generally, 1 is left, 2 is middle, 3 is right, 4 is wheel up, 5 is wheel down.
	ss = strndup(buf + 1, 1); // 2nd part of the command is the button code
	button = atoi(ss); // make it an int
	ss = strndup(buf + 2, 1); // 3rd part of the command is the number of clicks (default is 1)
	repeat = atoi(ss); // make it an int

	// repeat click protection
	if (repeat < 1){
		repeat= 1;
	} else if (repeat>2){
		repeat = 2;
	}

	printf("click_mouse button %i, %i times\n", button, repeat);
	xdo_click_multiple(IF_XDO, CURRENTWINDOW, button,repeat, 1500);
	return;
}


void type_char(char * buf) {
	// type the character
	char *ss = (char*) malloc(1);
	ss = strndup(buf + 1, 1); // 2nd part of the command is the letter to type
	printf("will type \"%s\"\n", ss);
	xdo_type(IF_XDO, CURRENTWINDOW, ss, 1200);
	return;
}
