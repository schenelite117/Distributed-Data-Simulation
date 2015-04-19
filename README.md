Stephen S Chen
USC ID: 6711434063

EE 450 Socket Programming Project README

***************************************************************
1. What have I done during this assignment?
In this assignment, I have learned a lot about socket programming. I coded all the files that
are included in this project. I have read Beej's tutorials and then online man pages. I've 
learned how to SSH into nunki and set up sublime text to run SFTP so that I can test natively
in nunki while coding. It has been a busy few weeks. Oh, and write this README.

***************************************************************
2. What does this code do?

dhtserver1.cpp + dhtserver1.h:
This code takes all the inputs from the textfile and creates a map to hold all of the values. 
It also creates all the sockets needed to run the designated server including the UDP socket 
and the dynamic TCP sockets to communicate with Server 2. It can communicate with the clients
It will also add new entries from Server 2 and 3 into the map if it doesn't have them originally. 
Also it will count how many clients have connected to the server in the same session. It outputs
the on-screen messages and initiates communication with Server 2. It will run in an infinite 
loop until the user types Ctrl+C to end the program. Will close its own sockets.

dhtserver2.cpp + dhtserver2.h:
This code also puts all the key value pairs from the textfile into a map for fast searching 
later. It creates the necessary sockets to return values to Server 1 or communicate with Server
3. It outputs the on-screen messages and adds new entries to the map as Server 3 replies with 
values that were not originally in Server 2's map. It also runs in an infinite loop. Will close
its own sockets.

dhtserver3.cpp + dhtserver3.h:
This code just has to create the necessary sockets to return values to Server 2 and output 
on-screen messages as it does its work. It also runs in an infinite loop. Will close its own
sockets.

client1.cpp + client1.h:
The client creates the one UDP socket it needs to communicate with the designated Server 1. It
also reads in the textfile and creates a map with all of those search terms and keys paired
as key-value pairs inside the map. It will be able to take in the user input and find the correct
search term in the map and retrieve the right key to use to query Server 1. It will also be able
to receive the values that are returned by the Server 1 and output all the required on-screen
messages while it is performing its functions. This code will run once and then terminate.

client2.cpp + client2.h:
This code is functionally identical to client1.


** All of the code includes error-checking wherever necessary.


***************************************************************
3. How to run this program?
I have included a makefile that will be able to help you compile the code. Run the makefile by typing:
make

The makefile will build 5 executables that you run as follows:
./server1
./server2
./server3
./client1
./client2

The names are pretty self-explanatory and if you wanted to run Server 1, just type ./server1. I have
all my source code in the folder /src and all the input files in the folder /input_files. Please do
not move any of these folders or the files that they contain from their places as this will cause 
the makefile to fail. The servers will all run in infinite loops until the user decides to terminate
them by using Ctrl+C. The clients will run once and then terminate automatically. 

To remove the executables for a clean build, type:
make clean
make

This will delete all the executables and then build them again.

***************************************************************
4. Format of all messages exchanged.
The libraries for socket programming are all using C code and not C++ so they take inputs of 
char arrays to send and receive messages between servers.

***************************************************************
5. Where does this project fail?
I have tested this project repeatedly and while there might be cases that I have not considered that
would cause this project to fail to meet the project specs, I have not encountered these errors yet. 
So to the best of my knowledge, my project doesn't fail.


***************************************************************
6. Reused Code?
I followed Beej's tutorial to create the sockets in all the cpp files when using getaddrinfo(). I have
marked these large sections off with comments as seen below:

/**
 *  @brief This socket starter code was taken out of the Beej's tutorial
 */

/**
 * @ end of code from Beej's tutorial
 */ 

You will find these sections in all of the .cpp and .h files. The .cpp files will have them when I am
creating the sockets (getaddrinfo, memset, socket, bind, sigaction, connect, setsockopt). I also reused 
the getsockname code from the project pdf. 








