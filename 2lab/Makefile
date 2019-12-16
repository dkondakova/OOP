CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
HEADERS=workflow.h worker.h parser.h validator.h executor.h
SOURCES=main.cpp worker.cpp workflow.cpp parser.cpp validator.cpp executor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=workflow

all: $(HEADERS) $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
