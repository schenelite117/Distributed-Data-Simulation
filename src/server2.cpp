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

int main() 
{
	std::ifstream ifile;
	ifile.open("input_files/server2.txt");

	// assume that the file input is well-formed and there are no invalid inputs in the file
	// save the file input into a map
	std::map<std::string, std::string> keymap;
	mapInputFile(ifile, &keymap);
	
	/**
	 * @brief This socket starter code was taken out of the Beej's tutorial
	 * This creates the static TCP socket for server 2
	 */
	struct addrinfo hints, *servinfo;
	memset (&hints, 0, sizeof hints); // zero the hints struct

	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP

	int status = getaddrinfo(NULL, "22000063", &hints, &servinfo);

	if (status != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	/**
	 * @ brief end of code from Beej's tutorial
	 */

	return 0;
}
