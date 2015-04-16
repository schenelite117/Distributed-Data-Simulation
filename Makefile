CXX=g++
CXXFLAGS=-g -Wall 
SUNFLAGS= -lsocket -lnsl -lresolv

# source code folders
SRC= src

# Uncomment for parser DEBUG
#DEFS=-DDEBUG

#OBJS=server1.o

all: server1 server2 server3 client1 client2
	# ./server1
	# ./server2
	# ./server3
	./client1
	# ./client2

# SERVER 1  ============================================
server1: $(SRC)/server1.cpp $(SRC)/server_util.h
	$(CXX) -o server1 $(SRC)/server1.cpp $(SUNFLAGS)


# SERVER 2  ============================================
server2: $(SRC)/server2.cpp $(SRC)/server_util.h
	$(CXX) -o server2 $(SRC)/server2.cpp $(SUNFLAGS)


# SERVER 3  ============================================
server3: $(SRC)/server3.cpp $(SRC)/server_util.h
	$(CXX) -o server3 $(SRC)/server3.cpp $(SUNFLAGS)


# CLIENT 1  ============================================
client1: $(SRC)/client1.cpp $(SRC)/client_util.h
	$(CXX) -o client1 $(SRC)/client1.cpp $(SUNFLAGS)

# CLIENT 2  ============================================
client2: $(SRC)/client2.cpp $(SRC)/client_util.h
	$(CXX) -o client2 $(SRC)/client2.cpp $(SUNFLAGS)


clean:
	rm -f *.o server1 server2 server3 client1 client2
