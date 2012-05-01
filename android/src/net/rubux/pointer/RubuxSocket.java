package net.rubux.pointer;

import java.net.*;

// http://developer.android.com/reference/android/view/VelocityTracker.html
// http://techtips.salon.com/connect-android-socket-server-1732.html
// http://www.java2s.com/Code/Java/Network-Protocol/SendoutUDPpockets.htm

public class RubuxSocket {
	/*
	 * Generate and send the UPD commands
	 */

	private static int RBX_PORT = 4950;
	private static String RBX_HOST = "192.168.0.3";
	private static float ACCELERATION = (float) 6.1;
	private static int PROPORTION = 49; // proportion

	/**
	 * @return the rBX_HOST
	 */
	public static String getRbxHost() {
		return RBX_HOST;
	}

	/**
	 * @param rBX_HOST
	 *            the rBX_HOST to set
	 */
	public void setRbxHost(String rBX_HOST) {
		RBX_HOST = rBX_HOST;
	}

	/**
	 * @return the rBX_PORT
	 */
	public static int getRbxPort() {
		return RBX_PORT;
	}

	/**
	 * @param rBX_PORT
	 *            the rBX_PORT to set
	 */
	public void setRbxPort(int rBX_PORT) {
		RBX_PORT = rBX_PORT;
	}

	public static void txMouseMove(float vx, float vy) {

		int nvx = (int) (getVector(vx));
		int nvy = (int) (getVector(vy));
		txMouseMove(nvx, nvy);
	}

	private static int getVector(float x) {
		float m = x / getAcceleration() ; // ratio of vector
		int p = getProportion();
		int v = (int) (m * p);

		if (v > p) { // clip it
			v = p;
		} else if (v < -p) {
			v = -p;
		}
		return v+p;
	}

	public static void txMouseMove(int vx, int vy) {
		try {
			// test: no move - send no packet
			int p = getProportion();
			if (vx ==  p && vy ==p){
				return;
			}
			
			final String msg = String.format("0%s%s", vx, vy);

			byte[] message = msg.getBytes();
			// byte[] hostbytes = getRbxHost().getBytes();

			// Get the internet address of the specified host
			InetAddress address = InetAddress.getByName(getRbxHost());

			// Initialize a datagram packet with data and address
			DatagramPacket packet = new DatagramPacket(message, message.length,
					address, getRbxPort());

			// Create a datagram socket, send the packet through it, close it.
			DatagramSocket dsocket = new DatagramSocket();
			dsocket.send(packet);
			dsocket.close();

		} catch (Exception e) {
			System.err.println(e);
		}
	}

	/**
	 * @return the aCCELERATION
	 */
	public static float getAcceleration() {
		return ACCELERATION;
	}

	/**
	 * @param aCCELERATION the aCCELERATION to set
	 */
	public static void setAcceleration(float aCCELERATION) {
		ACCELERATION = aCCELERATION;
	}

	/**
	 * @return the pROPORTION
	 */
	public static int getProportion() {
		return PROPORTION;
	}

	/**
	 * @param pROPORTION the pROPORTION to set
	 */
	public void setProportion(int p) {
		PROPORTION = p;
	}

}

//
// int send_message(char * hostname, char * msg) {
// int sockfd, numbytes;
// struct addrinfo hints, *servinfo, *p;
// int rv;
// memset(&hints, 0, sizeof hints);
// hints.ai_family = AF_UNSPEC;
// hints.ai_socktype = SOCK_DGRAM;
//
// if ((rv = getaddrinfo(hostname, SERVERPORT, &hints, &servinfo)) != 0) {
// fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
// return 1;
// }
//
// // loop through all the results and make a socket
// for (p = servinfo; p != NULL; p = p->ai_next) {
// if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
// == -1) {
// perror("talker: socket");
// continue;
// }
//
// break;
// }
//
// if (p == NULL) {
// fprintf(stderr, "talker: failed to bind socket\n");
// return 2;
// }
//
// if ((numbytes = sendto(sockfd, msg, strlen(msg), 0, p->ai_addr,
// p->ai_addrlen)) == -1) {
// perror("talker: sendto");
// exit(1);
// }
//
// freeaddrinfo(servinfo);
// printf("talker: sent %d bytes to %s\n", numbytes, hostname);
// close(sockfd);
//
// return 0;
// }

