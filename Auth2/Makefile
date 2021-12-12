CC=g++
CFLAGS=-Wall -g -O3 -std=c++17
ALLOC_DEP=/usr/local/lib/libmosquitto.so.1
ALLOC_LINK=$(ALLOC_DEP) -lpthread -ldl

PROGRAMS = publish subscribe1 subscribe2

all: $(PROGRAMS)
#all: publish subscribe

publish: 
	$(CC) $(CFLAGS) publish.cpp -o publish $(ALLOC_LINK)

subscribe1: 
	$(CC) $(CFLAGS) subscribe1.cpp -o subscribe1 $(ALLOC_LINK)

subscribe2: 
	$(CC) $(CFLAGS) subscribe2.cpp -o subscribe2 $(ALLOC_LINK)

clean:
	rm -f publish subscribe1 subscribe2
