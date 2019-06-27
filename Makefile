CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -W -pedantic -std=c++17 -g
EXEC=soft_heap
TEST= test_constructor.cpp
FILE=main.cc

.PHONY: run

all: $(EXEC)

soft_heap: $(FILE)
	$(CXX) -o $(EXEC) $(FILE) $(CXXFLAGS)

test:
	$(CXX) -o test $(TEST) $(CXXFLAGS)

run:
	./$(EXEC)

clean:
	rm -rf $(EXEC)
