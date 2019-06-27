CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -W -pedantic -std=c++17 -g
EXEC=soft_heap
TEST= tests/test_constructor.cpp tests/main.cpp
FILE= src/main.cc

.PHONY: run

all: $(EXEC)

soft_heap: $(FILE)
	$(CXX) -o $(EXEC) $(FILE) $(CXXFLAGS)

test:
	$(CXX) -o test $(TEST) $(CXXFLAGS)

test_soft:
	$(CXX) $(CXXFLAGS) tests/test.cc -o $(@)

run:
	./$(EXEC)

clean:
	rm -rf $(EXEC)
	rm -rf test
	$(RM) test_soft
