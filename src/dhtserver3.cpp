/**
 * By: Stephen Chen
 * EE450 Computer Networks: Socket Programming Project
 * DHT Server 3
 * 
 * --Start Server 3 code to be able to server 1's queries
 * and return values 
 */


#include <stdlib.h>
#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include "server_util.h"

#define LISTEN_PORT "23063" // port client hosts will be connecting to
#define BACKLOG 10

int main() 
{
	std::ifstream ifile;
	ifile.open("input_files/server3.txt");

	// assume that the file input is well-formed and there are no invalid inputs in the file
	// save the file input into a map
	std::map<std::string, std::string> keymap;
	mapInputFile(ifile, &keymap);
	
	/**
	 * @brief This socket starter code was taken out of the Beej's tutorial
	 * This creates the static TCP socket for server 3
	 */
	struct addrinfo hints, *servinfo; // for listen() socket
	struct sockaddr_storage clientAddr; // for accept() socket
	socklen_t clientAddrSize;

	/** socket file descriptors **/
	int listClientSock; // to bind to listen() socket
	int newSock; // accept() socket for send() and recv()


	memset (&hints, 0, sizeof hints); // zero the hints struct

	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP

	int status = getaddrinfo("nunki.usc.edu", LISTEN_PORT, &hints, &servinfo);

	if (status != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	/**
	 * @ brief end of code from Beej's tutorial
	 */

	for (addrinfo* p = servinfo; p != NULL; p = p->ai_next) 
	{
		// create the socket file descriptor
		listClientSock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

		if (listClientSock != -1) 
		{
			break; // if found a valid socket, break
		}

	}

	
	// allow to reuse the active port if no one else is listening on that port
	// also obtained from Beej's tutorial
	char yes = '1';
	if (setsockopt(listClientSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(char)) == -1)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// bind the socket
	bind(listClientSock, servinfo->ai_addr, servinfo->ai_addrlen);
	
	// listen for incoming communications
	listen(listClientSock, BACKLOG);

	// accept any incoming connections and return a new socket file descriptor to send() and recv()
	clientAddrSize = sizeof clientAddr;
	newSock = accept(listClientSock, (struct sockaddr *)& clientAddr, &clientAddrSize);

	freeaddrinfo(servinfo);

	return 0;
}
