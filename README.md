Stephen S Chen
USC ID: 6711434063

EE 450 Socket Programming Project README

***************************************************************
1. What does this code do?

dhtserver1.cpp


dhtserver2.cpp


dhtserver3.cpp


client1.cpp


client2.cpp




***************************************************************
2. How to run this program?

Makefile



***************************************************************
3. Format of all messages exchanged.




***************************************************************
4. Where does this project fail?



***************************************************************
5. Reused Code?
- I followed Beej's tutorial to create the sockets in all the cpp
files when using getaddrinfo(). Also to setsockopt(), to make sure
that my code can reuse the statically assigned ports if they no
other process is actively using that port.