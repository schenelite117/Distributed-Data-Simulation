##Distributed Database Simulation README

***************************************************************
###Overview:

This project was completed to fulfill the project requirements for the final project of USC's
EE450 curriculum. We were required to demonstrate knowledge of socket programming by developing
a distributed database simulation. The simulation starts with the client process submitting a
user query in terms of a 5 character key value to the Server 1 process. All 3 servers are initialized
with a map of 4 key-value pairs mapping a 5 character key to a 7 character value. There are 12 
key-value pairs in total and each server has a different set of 4 key-value pairs. After the 
client submits its query, the Server 1 will attempt to match the query with the solution in its
database. If a solution is found, it will return the solution string along the UDP socket to the
client. But if a solution isn't found, it will recursively submit the query to Server 2 which will
submit the query to Server 3 if a solution is still not found. Whenever either Server 2 or 3 returns 
a solution, the previous Server will cache the solution into its database by creating a new key-value 
pair mapping the solution received with the query that was submitted. Then it will pass the solution
back to the client. If a solution is not found at Server 3, the client will also be notified.

***************************************************************
###1. What have I done during this assignment?

+ Created a distributed database model in C++ using C socket programming libraries
+ Conducted client-server communications using UDP sockets
+ Conducted server-server communications using TCP sockets
+ Enabled information querying by the client process
+ Servers unable to answer a query will recursively submit the query to other servers
+ Fixed Port numbers: Server 1 - "21063", Server 2 - "22063", Server 3 - "23063"
+ IP address has been set to localhost so that this simulation can run on any machine

***************************************************************
###2. What does this code do?

####dhtserver1.cpp + dhtserver1.h:
This code takes all the inputs from the textfile and creates a map to hold all of the values. 
It also creates all the sockets needed to run the designated server including the UDP socket 
and the dynamic TCP sockets to communicate with Server 2. It can communicate with the clients
It will also add new entries from Server 2 and 3 into the map if it doesn't have them originally. 
Also it will count how many clients have connected to the server in the same session. It outputs
the on-screen messages and initiates communication with Server 2. It will run in an infinite 
loop until the user types Ctrl+C to end the program. Will close its own sockets.

####dhtserver2.cpp + dhtserver2.h:
This code also puts all the key value pairs from the textfile into a map for fast searching 
later. It creates the necessary sockets to return values to Server 1 or communicate with Server
3. It outputs the on-screen messages and adds new entries to the map as Server 3 replies with 
values that were not originally in Server 2's map. It also runs in an infinite loop. Will close
its own sockets.

####dhtserver3.cpp + dhtserver3.h:
This code just has to create the necessary sockets to return values to Server 2 and output 
on-screen messages as it does its work. It also runs in an infinite loop. Will close its own
sockets.

####client1.cpp + client1.h:
The client creates the one UDP socket it needs to communicate with the designated Server 1. It
also reads in the textfile and creates a map with all of those search terms and keys paired
as key-value pairs inside the map. It will be able to take in the user input and find the correct
search term in the map and retrieve the right key to use to query Server 1. It will also be able
to receive the values that are returned by the Server 1 and output all the required on-screen
messages while it is performing its functions. This code will run once and then terminate.

####client2.cpp + client2.h:
This code is functionally identical to client1.

Additionally, all of the code includes error-checking wherever necessary.


***************************************************************
###3. How to run this program?
I have included a makefile that will be able to help you compile the code. Run the makefile by typing:
'make'

The makefile will build 5 executables that you run as follows:
./server1
./server2
./server3
./client1
./client2

In three separate terminal processes, run ./server1, ./server2, and ./server3.


The servers will all run continuously until the user decides to terminatethem by using Ctrl+C. If the 
user doesn't terminate these server processes when finished with the simulation, they will become zombie
processes and be destroyed when the user reboots the machine. Otherwise, use the following commands to 
remove the zombie processes:

ps –aux | grep <your username>
kill -9 <process number>

The clients will run once and then terminate automatically. Use the server#.txt for a list of acceptable 
keys to query.

To remove the executables for a clean build, type:
'make clean'
'make'

This will delete all the executables and then build them again.

***************************************************************
###4. Format of all messages exchanged.

The libraries for socket programming are all using C code and not C++ so they take inputs of 
char arrays to send and receive messages between servers.

***************************************************************
###5. Where does this project fail?

I have tested this project repeatedly and while there might be cases that I have not considered that
would cause this project to fail to meet the project specs, I have not encountered these errors yet. 
So to the best of my knowledge, my project doesn't fail. However, this project has been designed in
accordance with the project's specs and was not tested to run on any server outside of USC's nunki's
server machines. In order to test this simulation on another machine, just replace nunki.usc.edu with
the address of that machine.

***************************************************************
###6. Reused Code?

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







