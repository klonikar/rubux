/*
 * actions.c
 *
 *  To also be used with the client for building the correct commands
 *  Created on: 15 Mar 2012
 *      Author: gareth
 */


enum IFXDO_ACTIONS {
	MOUSE_MOVE, MOUSE_BUTTON, MOUSE_DOWN, MOUSE_UP,
	KEYUP, KEYSTROKE, KEYDOWN
};


enum MOUSE_BUTTON {
	LEFT, MIDDLE, RIGHT, WHEEL_UP, WHEEL_DOWN
};

enum MOUSE_ACTION {
	CLICK, DOWN, UP
};
