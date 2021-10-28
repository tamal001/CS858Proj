CC=g++
CFLAGS=-Wall -g -O3 -std=c++17
ALLOC_DEP=/usr/local/lib/libmosquitto.so.1
ALLOC_LINK=$(ALLOC_DEP) -lpthread -ldl

PROGRAMS = publish subscribe

all: $(PROGRAMS)
#all: publish subscribe

publish: 
	$(CC) $(CFLAGS) publish.cpp -o publish $(ALLOC_LINK)

subscribe: 
	$(CC) $(CFLAGS) subscribe.cpp -o subscribe $(ALLOC_LINK)

clean:
	rm -f publish subscribe
