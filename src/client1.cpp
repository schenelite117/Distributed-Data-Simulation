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

#include "client1.h"

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
	struct sockaddr_in servAddr; // for storing server info socket
	struct sockaddr_in myAddr;
	
	struct in_addr** serverIP; // getting server's IP 
	struct hostent* servhost; // server host info

	socklen_t servAddrSize;
	socklen_t myAddrSize;


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

	// save the port and ip info for cSock
	struct sockaddr_in* s = (struct sockaddr_in *)p->ai_addr;

	if (p == NULL) 
	{
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}
	/**
	 * @ end of code from Beej's tutorial
	 */

	std::string input = userInput(keymap);
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
	std::cout << "The Client 1 sends the request " << input << " to the Server 1 with port number " << SERVER_PORT;

	// get the host info
	if ((servhost = gethostbyname("nunki.usc.edu")) == NULL) {  
    	herror("gethostbyname");
    	return 2;
	}
	serverIP = (struct in_addr **)servhost->h_addr_list;
	std::cout << " and\nIP address " << inet_ntoa(*serverIP[0]) << std::endl;

	// get client's info, reused from project pdf
	int stat = getsockname(cSock, (struct sockaddr *)&myAddr, &myAddrSize);
	if (stat == -1)
	{
		perror("getsockname");
		exit(EXIT_FAILURE);
	} 
	// end reused from project pdf
	
	std::cout << "The Client1's port number is " << ntohs(myAddr.sin_port);
	std::cout << " and the IP address is " << inet_ntoa(s->sin_addr) << std::endl;

	char buf[MAXDATASIZE];
	for (int i = 0; i < MAXDATASIZE; i++) 
	{
		buf[i] = '\0'; // overwrite buffer with all null characters
	}

	servAddrSize = sizeof(servAddr);
	recvfrom(cSock, buf, MAXDATASIZE, 0, (struct sockaddr *)&servAddr, &servAddrSize);
	std::string val(buf);

	// screen messages after receiving the reply
	std::cout << "The Client 1 received the value " << val << " from the Server 1 with port number ";
	std::cout << ntohs(servAddr.sin_port) << " and\nIP address is " << inet_ntoa(servAddr.sin_addr) << std::endl;

	std::cout << "The Client1's port number is " << ntohs(myAddr.sin_port);
	std::cout << " and the IP address is " << inet_ntoa(s->sin_addr) << std::endl;

	val.erase(val.begin(), val.begin()+5); // Erase the POST message in front

	std::cout << "The requested value is " << val << "\n" << std::endl;


	freeaddrinfo(servinfo);
	close(cSock);

	return 0;
}
