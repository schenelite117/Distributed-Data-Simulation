/**
 * By: Stephen Chen
 * EE450 Computer Networks: Socket Programming Project
 * Client 2
 * 
 * --Start Client 2 code to be able to query user search inputs 
 * use the input file to find key values and return results from
 * servers
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

#include "client_util.h"


int main() 
{
	std::ifstream ifile;
	ifile.open("input_files/client2.txt");

	// assume that the file input is well-formed and there are no invalid inputs in the file
	// save the file input into a map
	std::map<std::string, std::string> keymap;
	mapInputFile(ifile, &keymap);
	outputTest(keymap);



	// std::map<std::string, std::string>::iterator it;
	// std::cout << "Printing Contents" << std::endl;
	// std::cout << keymap.size() << std::endl;
	// for (it = keymap.begin(); it != keymap.end(); ++it)
	// {
	// 	std::cout << it->first << " " << it->second << std::endl;
	// }


	addrinfo hints, *servInfo;
	// call memset zero on the hints structure

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM; // UDP

	return 0;
}


