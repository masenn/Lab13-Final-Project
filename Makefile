CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lncurses -lm
SOURCES=main.c wav.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all:$(SOURCES)$(EXECUTABLE)

#pull in dependency info for exisitng .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $<> $*.d

clean:
	rm -rf $(OBJECTS)$(EXECUTABLE)