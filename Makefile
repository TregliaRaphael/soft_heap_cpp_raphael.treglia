CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -W -pedantic -std=c++17 -g
EXEC=soft_heap
FILE=main.cc

.PHONY: run

all: $(EXEC)

soft_heap: $(FILE)
	$(CXX) -o $(EXEC) $(FILE) $(CXXFLAGS)

run:
	./$(EXEC)

clean:
	rm -rf $(EXEC)
