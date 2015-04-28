CC = g++
CC_FLAGS = -lstdc++ -I "../../rapidjson/include"

all: server client

server: server.cpp
	$(CC) -o server.run server.cpp $(CC_FLAGS)
client: client.cpp
	$(CC) -o client.run client.cpp $(CC_FLAGS)

clean:
	rm -rf *.run
