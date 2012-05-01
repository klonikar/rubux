/*
 * client.c -- a datagram client for sending xdo messages
 *
 * Brian "Beej Jorgensen" Hall "Beej's Guide to Network Programming"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT "4950"    // the port users will be connecting to

int send_message(char * hostname, char * msg) {
	int sockfd, numbytes;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(hostname, SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("talker: socket");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to bind socket\n");
		return 2;
	}

	if ((numbytes = sendto(sockfd, msg, strlen(msg), 0, p->ai_addr,
			p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}

	freeaddrinfo(servinfo);
	printf("talker: sent %d bytes to %s\n", numbytes, hostname);
	close(sockfd);

	return 0;
}

int client(char * hostname) {

//	send_message(hostname, "011");
//	send_message(hostname, "099");
//	send_message(hostname, "059");
//	send_message(hostname, "051");
//	send_message(hostname, "095");
//	send_message(hostname, "015");
	send_message(hostname, "5h");
	send_message(hostname, "5e");
	send_message(hostname, "5l");
	send_message(hostname, "5l");
	send_message(hostname, "5o");
	send_message(hostname, "11");
	send_message(hostname, "13");
	send_message(hostname, "exit");
	return 0;
}

