CXX=g++
CXXFLAGS=-g -Wall 
SUNFLAGS= -lsocket -lnsl -lresolv

# Uncomment for parser DEBUG
#DEFS=-DDEBUG

#OBJS=server1.o

all: server1 server2 server3 client1 client2
	./server1
	./server2
	./server3
	./client1
	./client2

# SERVER 1  ============================================
server1: server1.cpp
	$(CXX) -o server1 server1.cpp $(SUNFLAGS)


# SERVER 2  ============================================
server2: server2.cpp
	$(CXX) -o server2 server2.cpp $(SUNFLAGS)


# SERVER 3  ============================================
server3: server3.cpp
	$(CXX) -o server3 server3.cpp $(SUNFLAGS)


# CLIENT 1  ============================================
client1: client1.cpp
	$(CXX) -o client1 client1.cpp $(SUNFLAGS)

# CLIENT 2  ============================================
client2: client2.cpp
	$(CXX) -o client2 client2.cpp $(SUNFLAGS)


clean:
	rm -f *.o server1 server2 server3 client1 client2
