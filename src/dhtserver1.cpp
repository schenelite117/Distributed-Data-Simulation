/**
 * By: Stephen Chen
 * EE450 Computer Networks: Socket Programming Project
 * DHT Server 1
 * 
 * --Start Server 1 code to be able to listen for client calls
 * and return values paired with the keys sent. Also can communicate
 * with Servers 2 and 3 to obtain any values that is not in server1.txt
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "server_util.h"

/** All the defines **/
#define LISTEN_PORT "21063" // port client hosts will be connecting to
#define BACKLOG 10
#define BUF_LEN 100



int main() 
{
	std::ifstream ifile;
	ifile.open("input_files/server1.txt");

	// assume that the file input is well-formed and there are no invalid inputs in the file
	// save the file input into a map
	std::map<std::string, std::string> keymap;
	mapInputFile(ifile, &keymap);
	
	/**
	 * @brief This socket starter code was taken out of the Beej's tutorial
	 * This creates the static UDP socket for server 1
	 */
	struct addrinfo hints, *servinfo; 
	struct sockaddr clientAddr; // for storing client info socket
	struct sigaction sa; // for removing zombie processes
	socklen_t clientAddrSize;

	/** socket file descriptors **/
	int listClientSock; // to bind to recvfrom() socket

	char yes = '1';


	// zero the hints struct
	memset (&hints, 0, sizeof hints); 

	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_DGRAM; // UDP

	int status = getaddrinfo("nunki.usc.edu", LISTEN_PORT, &hints, &servinfo);

	// if there's an error with getaddrinfo it will return non-zero value
	if (status != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return 1;
	}
	

	// walk through linked list to make sure that there is a valid address info 
	addrinfo* p;
	for (p = servinfo; p != NULL; p = p->ai_next) 
	{
		// create the socket file descriptor
		// connect to the first socket description available
		if ((listClientSock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
		{
			perror("server: socket");
			continue; // if invalid socket, keep looping
		}

		// allow to reuse the active port if no one else is listening on that port
		
		// if (setsockopt(listClientSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(char)) == -1)
		// {
		// 	perror("setsockopt");
		// 	exit(EXIT_FAILURE);
		// }
	

		// bind the socket
		if (bind(listClientSock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
		{
			close(listClientSock);
			perror("server: bind");
			continue;
		}
		
		break;

	}

	if (p == NULL) 
	{
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	freeaddrinfo(servinfo);

	// sigaction is to destroy all zombie processes just in case I want to fork() later
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}

	/**
	 * @ end of code from Beej's tutorial
	 */

	// use recvfrom() to receive any incoming connections 
	char buf[BUF_LEN];
	for (int i = 0; i < BUF_LEN; i++) 
	{
		buf[i] = '\0'; // overwrite buffer with all null characters
	}

	clientAddrSize = sizeof(clientAddr);
	recvfrom(listClientSock, buf, BUF_LEN, 0, &clientAddr, &clientAddrSize);

	std::string key (buf);
	key.erase(key.begin(), key.begin()+4); //erase the GET message in front

	if (keymap.find(key) != keymap.end())
	{
		std::string value = "POST " + keymap.find(key)->second;
		const char* keyvalue = value.c_str();
		int msg_length = strlen(keyvalue);
		int sent = 0;
		do {
			if ((sent = sendto(listClientSock, keyvalue, msg_length, 0, &clientAddr, clientAddrSize))==-1) 
			{
	    		perror("server: sendto");
	    		break;
			}
			msg_length -= sent;
		} while(msg_length > 0);
	}

	close(listClientSock);
	return 0;
}
