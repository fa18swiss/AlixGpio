CC = g++
CC_FLAGS = -lstdc++ -I "../../rapidjson/include"

all: client

client: client.cpp
	$(CC) -o client.run client.cpp $(CC_FLAGS)

clean:
	rm -rf *.run
