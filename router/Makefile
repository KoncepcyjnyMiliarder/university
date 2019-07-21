CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++11 -Werror -I.
LDLIBS = -lstdc++
TARGETS = router

all: router

router: main.o ip_helpers.o router.o

main.o: main.cpp

ip_helpers.o: ip_helpers.cpp

router.o: router.cpp

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)
