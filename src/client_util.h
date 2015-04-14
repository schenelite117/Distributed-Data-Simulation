#ifndef CLIENT_UTIL
#define CLIENT_UTIL

#include <iostream>
#include <string>
#include <map>
#include <fstream>

// function prototypes
void mapInputFile(std::ifstream&, std::map<std::string, std::string>*);
void error(const char*);
void outputTest(std::map<std::string, std::string>);

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

void error(const char* msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}



#endif
