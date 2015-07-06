#ifndef CLIENT1
#define CLIENT1

#include <iostream>
#include <string>
#include <map>
#include <fstream>

// function prototypes
void mapInputFile(std::ifstream&, std::map<std::string, std::string>*);
void error(const char*);
void outputTest(std::map<std::string, std::string>);
std::string userInput();
void *get_in_addr(struct sockaddr*);

/**
 *  Start Code
 */

// read the file and map the key value pairs in a map
void mapInputFile(std::ifstream& ifile, std::map<std::string, std::string>& keymap)
{
	std::string input, search, key;
	while (ifile >> input) 
	{
		// first input is the search term
		search = input;
		// second input is the key
		ifile >> input;
		key = input;

		keymap.insert(std::make_pair(search, key));
	}
}

// test the validity of the map by iterating through it and outputting 
// the key-value pairs
void outputTest(std::map<std::string, std::string>& keymap) 
{
	std::map<std::string, std::string>::iterator it;
	for (it = keymap.begin(); it != keymap.end(); ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

}



// get a search term from the user and retrieve the respective key value 
// associated with the term
std::string userInput(std::map<std::string, std::string>& keymap) 
{
	std::string input;
	do {
		std::cout << "Please Enter Your Search (USC, UCLA, etc.):  ";
		std::cin >> input;

	} while (keymap.find(input) == keymap.end() && input != "0");

	return input;
}

/**
 * copied from Beej's tutorial
 */
// output the error if one occurs then quits the program
void error(const char* msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}
 
// get sockaddr, IPv4
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
}
/**
 * end copied from Beej's tutorial
 */

#endif
