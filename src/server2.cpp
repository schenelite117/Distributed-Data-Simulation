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

#include <iostream>
#include <fstream>

int main() 
{
	// fstream


	// addrinfo hints, *servInfo;
	// call memset zero on the hints structure

	// hints.ai_family = AF_INET;
	// hints.ai_socktype = SOCK_STREAM; TCP
	// hints.ai_socktype = SOCK_DGRAM; UDP

	// outputs linked list of sockaddr structures that can create a socket from and outputs to servInfo
	// int it returns is for error checking
	// int = getaddrinfo(serverIPaddress (string), servertcpport (string), &hints, &servInfo);

	// loop through linked list 
	// declare integer for socket file descriptor
	// for (p = servInfo, p != NULL; p= p->ai_next){ 
	// 		call the socket(p->ai_family, p->ai_socktype, p->ai_protocol) and save into the int
	//		check to see if the int is -1, if so it is an error then keep looping using continue
	//		once you have a socket you call connect(int, p->ai_addr, p->ai_addrlen)
	//		check if connect returned a -1 then error and close socket, continue
	//		break
	// error check p if null then not able to create a socket
	// free addrinfo information (servinfo)
	// do-while loop to send
	// send (socket descriptor int, string want to send, length remaining, flags) - returns how many bytes were sent
	// length remaining should be set to the string length that
	// recv(socket descriptor int, receive buffer, how long is the buffer, flags) - returns how many bytes were received
	// zero out receive buffer and receive blocks execution
	// close sockets
	//
	// UDP main difference is you don't need to connect, use sendto(same 4 as tcp, p->addr, p->ai_addrlen) and recvfrom()



	std::cout << "Server2" << std::endl;
	return 0;
}
