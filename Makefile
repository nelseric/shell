CC=gcc
CFLAGS=-Wall -std=c99 -ggdb 
LDLIBS=-lreadline
LDFLAGS=-ggdb

SOURCES=shell.c

OBJECTS=$(SOURCES:.c=.o)

TARGET=jbash #Jason Bourne Shell


.PHONY : clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(OBJECTS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.depend: depend 


depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;
include .depend

run: all
	./$(TARGET) 
clean:
	rm $(OBJECTS) $(TARGET) 

