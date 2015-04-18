/**
 * By: Stephen Chen
 * EE450 Computer Networks: Socket Programming Project
 * Client 1
 * 
 * --Start Client 1 code to be able to query user search inputs 
 * use the input file to find key values and return results from
 * servers
 */


#include <cstdlib>
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

#include "client_util.h"

#define MAXDATASIZE 100 // max number of bytes we can get at once
#define SERVER_PORT "21063"

/**
 * Start Main
 */

int main() 
{
	std::ifstream ifile;
	ifile.open("input_files/client1.txt");

	// assume that the file input is well-formed and there are no invalid inputs in the file
	// save the file input into a map
	// std::string input, search, key;
	std::map<std::string, std::string> keymap;
	mapInputFile(ifile, keymap);


	/**
	 * @brief This socket starter code was taken out of the Beej's tutorial
	 */
	int cSock, numbytes;
	struct addrinfo hints, *servinfo;
	struct sockaddr servAddr; // for storing server info socket
	socklen_t servAddrSize;


	memset (&hints, 0, sizeof hints); // zero the hints struct

	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_DGRAM; // UDP	

	// outputs linked list of sockaddr structures that can create a socket from and outputs to servinfo
	int status = getaddrinfo("nunki.usc.edu", SERVER_PORT, &hints, &servinfo);

	if (status != 0)	
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	addrinfo* p;
	for (p = servinfo; p != NULL; p = p->ai_next) 
	{
		// create the socket file descriptor
		if ((cSock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
		{
			perror("client: socket");
			continue; // if invalid socket, keep looping
		}

		break;
	}

	if (p == NULL) 
	{
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}
	/**
	 * @ end of code from Beej's tutorial
	 */
	while (1) 
	{
		std::string input = userInput(keymap);
		if (input == "0")
			break;
		std::cout << "The Client 1 has received a request with search word " << input;
		std::cout << ", which maps to key " << keymap.find(input)->second << "." << std::endl;

		input = "GET " + keymap.find(input)->second;
		const char* keyvalue = input.c_str() + '\0';

		int msg_length = strlen(keyvalue);
		int sent = 0;

		do {
			if ((sent = sendto(cSock, keyvalue, msg_length, 0, p->ai_addr,p->ai_addrlen))==-1) 
			{
	    		perror("client: sendto");
	    		break;
			}
			msg_length -= sent;
		} while(msg_length > 0);
		std::cout << "The Client 1 sends the request " << input << " to the Server 1 with port number " << std::endl;

		// length remaining should be set to the string length that
		// recv(socket descriptor int, receive buffer, how long is the buffer, flags) - returns how many bytes were received

		char buf[MAXDATASIZE];
		for (int i = 0; i < MAXDATASIZE; i++) 
		{
			buf[i] = '\0'; // overwrite buffer with all null characters
		}

		servAddrSize = sizeof(servAddr);
		recvfrom(cSock, buf, MAXDATASIZE, 0, &servAddr, &servAddrSize);

		std::string val(buf);
		val.erase(val.begin(), val.begin()+5); // Erase the POST message in front

		std::cout << "The requested value is " << val << std::endl;
	}

	freeaddrinfo(servinfo);
	close(cSock);

	return 0;
}
