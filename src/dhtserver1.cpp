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
#define SERV_PORT "22063"	// port to server 2's TCP socket
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
	struct addrinfo hints, *servinfo; // for static UDP socket
	struct addrinfo servHints, *serverinfo; // for dynamic TCP socket
	struct sockaddr clientAddr; // for storing client info socket
	struct sigaction sa; // for removing zombie processes
	socklen_t clientAddrSize;

	/** socket file descriptors **/
	int listClientSock; // to bind to recvfrom() socket
	int servSock; // TCP connection to server 2

	int yes = 1;


	// zero the hints struct
	memset (&hints, 0, sizeof hints); 
	memset (&servHints, 0, sizeof servHints);

	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_DGRAM; // UDP

	servHints.ai_family = AF_INET;
	servHints.ai_socktype = SOCK_STREAM; // TCP

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
			perror("server: static UDP socket");
			continue; // if invalid socket, keep looping
		}

		// allow to reuse the active port if no one else is listening on that port
		
		if (setsockopt(listClientSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			perror("setsockopt");
			exit(EXIT_FAILURE);
		}
	
		// bind the socket
		if (bind(listClientSock, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(listClientSock);
			perror("server: static UDP bind");
			continue;
		}
	

		break;

	}

	struct sockaddr_in* s = (struct sockaddr_in *)p->ai_addr;
	std::cout << "The Server 1 has UDP port number " << ntohs(s->sin_port);
	std::cout << " and the IP address is " << inet_ntoa(s->sin_addr) << std::endl;

	if (p == NULL) 
	{
		fprintf(stderr, "server: static UDP socket failed to bind\n");
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

	// go into a server loop
	int counter = 1;
	while (1) 
	{
		// use recvfrom() to receive any incoming connections 
		char buf[BUF_LEN];
		for (int i = 0; i < BUF_LEN; i++) 
		{
			buf[i] = '\0'; // overwrite buffer with all null characters
		}

		clientAddrSize = sizeof(clientAddr);
		recvfrom(listClientSock, buf, BUF_LEN, 0, &clientAddr, &clientAddrSize);
		s = (struct sockaddr_in *)&clientAddr;
		std::cout << "The Server 1 has received a request " << buf << " from Client " << counter << " with port number ";
		std::cout << ntohs(s->sin_port) << " and\nIP address " << inet_ntoa(s->sin_addr) << std::endl;

		std::string key (buf);
		key.erase(key.begin(), key.begin()+4); //erase the GET message in front

		// if can find the key in server 1
		if (keymap.find(key) != keymap.end())
		{
			std::string value = "POST " + keymap.find(key)->second;
			const char* keyvalue = value.c_str();
			int msg_length = strlen(keyvalue);
			int sent = 0;
			do {
				if ((sent = sendto(listClientSock, keyvalue, msg_length, 0, &clientAddr, clientAddrSize))==-1) 
				{
		    		perror("server: static UDP socket sendto");
		    		break;
				}
				msg_length -= sent;
			} while(msg_length > 0);

			std::cout << "The Server 1 sends the reply " << value << " to Client " << counter << " with port number ";
			std::cout << ntohs(s->sin_port) << " and\nIP address " << inet_ntoa(s->sin_addr) << std::endl;

		} 
		else // check server 2 using a TCP connection
		{ 

			/**
	 		* @brief This socket starter code was taken out of the Beej's tutorial
	 		* This creates the TCP socket for server 1
	 		*/
			int stat = getaddrinfo("nunki.usc.edu", SERV_PORT, &servHints, &serverinfo);

			// if there's an error with getaddrinfo it will return non-zero value
			if (stat != 0)
			{
				fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(stat));
				return 1;
			}
		

			// walk through linked list to make sure that there is a valid address info 
			addrinfo* p2;
			for (p2 = serverinfo; p2 != NULL; p2 = p2->ai_next) 
			{
				// create the socket file descriptor
				// connect to the first socket description available
				if ((servSock = socket(p2->ai_family, p2->ai_socktype, p2->ai_protocol)) == -1) 
				{
					perror("server: TCP socket");
					continue; // if invalid socket, keep looping
				}

				// allow to reuse the active port if no one else is listening on that port
				
				if (setsockopt(listClientSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
				{
					perror("setsockopt");
					exit(EXIT_FAILURE);
				}
			

				// connect the socket
				if (connect(servSock, serverinfo->ai_addr, serverinfo->ai_addrlen) == -1)
				{
					close(servSock);
					perror("server: TCP socket connect");
					continue;
				}
				break;
			}

			if (p == NULL) 
			{
				fprintf(stderr, "server: TCP socket failed to connect\n");
				return 2;
			}

			/**
	 		* @ end of code from Beej's tutorial
	 		*/

			// forwarding GET request to server 2

			std::string fwKey = "GET " + key;
			const char* keyvalue = fwKey.c_str() + '\0';

			int msg_length = strlen(keyvalue);
			int sent = 0;

			do {
				if ((sent = send(servSock, keyvalue, msg_length, 0))==-1) 
				{
		    		perror("server: TCP socket send");
		    		break;
				}
				msg_length -= sent;
			} while(msg_length > 0);

			freeaddrinfo(serverinfo);

			// recv response from server 2 then return response to client
			for (int i = 0; i < BUF_LEN; i++) 
			{
				buf[i] = '\0'; // overwrite buffer with all null characters
			}
			clientAddrSize = sizeof(clientAddr);
			recv(servSock, buf, BUF_LEN, 0);

			close(servSock); // close the connection with server 2
			
			std::cout << buf << std::endl;
			std::string val(buf);
			val.erase(val.begin(), val.begin()+5); // Erase the POST message in front

			// save an entry into the map
			keymap.insert(std::make_pair(key,val));

			// relay back to client
			msg_length = strlen(buf);
			sent = 0;
			do {
				if ((sent = sendto(listClientSock, buf, msg_length, 0, &clientAddr, clientAddrSize))==-1) 
				{
		    		perror("server: static UDP socket sendto");
		    		break;
				}
				msg_length -= sent;
			} while(msg_length > 0);
		}
		counter++;
	}


	close(listClientSock);
	return 0;
}
