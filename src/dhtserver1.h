#ifndef DHTSERVER1
#define DHTSERVER1

#include <iostream>
#include <string>
#include <map>
#include <fstream>

// function prototypes
void mapInputFile(std::ifstream&, std::map<std::string, std::string>*);
void error(const char*);
void outputTest(std::map<std::string, std::string>);
void *get_in_addr(struct sockaddr*);
void sigchld_handler(int);


/**
 *  Start Code
 */

// return 1 if there was an error in reading the file
void mapInputFile(std::ifstream& ifile, std::map<std::string, std::string>* keymap)
{
	std::string input, search, key;
	while (ifile >> input) 
	{
		// first input is the search term
		search = input;
		// second input is the key
		ifile >> input;
		key = input;

		keymap->insert(std::make_pair(search, key));
	}
}

void outputTest(std::map<std::string, std::string> keymap) 
{
	std::map<std::string, std::string>::iterator it;
	for (it = keymap.begin(); it != keymap.end(); ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

}

/**
 * copied from Beej's tutorial
 */
// get sockaddr, IPv4
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
}
// output the error if one occurs then quits the program
void error(const char* msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}

void sigchld_handler(int s)
{
	while (waitpid(-1, NULL,WNOHANG) > 0);
}
/**
 * end copied from Beej's tutorial
 */


#endif
