/*
 * rubux.c
 *
 *  Created on: 19 Mar 2012
 *      Author: gareth
 */

#include <stdio.h>
#include <unistd.h>

#define PROG_NAME "rubux"
#define PROG_VER  "0.1"

static void usage(void) {
	fprintf(stderr, "usage: rubux -c <hostname>\n");
	fprintf(stderr, "Usage: " PROG_NAME " [required_options] [optional_options]\n");
	fprintf(stderr, "\n\t[required_options] (select only one) \n");
	fprintf(stderr,"\t-s serve on localhost\n");
	fprintf(stderr,"\t-c <hostname> client mode to connect to server on <hostname>\n");
}

static void unittest(void){
	fprintf(stderr, "TODO: self test code here\n");
}

int main(int argc, // Number of strings in array argv
		char *argv[], // Array of command-line argument strings
		char **envp) // Array of environment variable strings
{
// user options
	int verbose = 0;
	int debug = 0;
	char ch;

	while ((ch = getopt(argc, argv, "c:shellovdu")) != EOF) {
		switch (ch) {
		case 'v':
			verbose = 1;
		case 'd':
			debug = 1;
		case 'c':
			client(optarg);
			break;
		case 's':
			server();
			break;
		case 'u':
			unittest();
			break;
		default:
			usage();
		}
	}
	return 0;
}
