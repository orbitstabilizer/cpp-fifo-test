CC = g++
CPPFLAGS = -std=c++11

all: writer.cpp reader.cpp
	$(CC) $(CPPFLAGS) -o writer writer.cpp
	$(CC) $(CPPFLAGS) -o reader reader.cpp
