CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++11 -Werror -I.
LDLIBS = -lstdc++
TARGETS = transport

SOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:.cpp=.o)
all: transport

transport: $(OBJS)

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)
