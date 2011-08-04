CC=gcc
CFLAGS=-Wall -std=c99 -ggdb 
LDLIBS=-lreadline
LDFLAGS=-ggdb

SOURCES=shell.c
HEADERS=shell.h

OBJECTS=$(SOURCES:.c=.o)

TARGET=shell


.PHONY : clean run package

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
	rm $(OBJECTS) $(TARGET) $(TARGET).tar.gz
package:
	tar -czvf $(TARGET).tar.gz $(SOURCES) $(HEADERS) Makefile
