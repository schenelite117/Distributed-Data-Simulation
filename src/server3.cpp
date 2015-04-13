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

int main() 
{
	freopen("server3.txt", "r", stdin);

	std::cout << "Server3" << std::endl;
	return 0;
}
