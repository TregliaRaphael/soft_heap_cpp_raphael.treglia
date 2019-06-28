CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -W -pedantic -std=c++17 -g
EXEC=soft_heap tricky_test

TEST= tests/test_constructor.cpp tests/main.cpp tests/test_insert.cpp
FILE= src/main.cc

.PHONY: run
.PHONY: clean

all: $(EXEC)


soft_heap: $(FILE)
	$(CXX) -o $(EXEC) $(FILE) $(CXXFLAGS)

test:
	$(CXX) $(CXXFLAGS) $(TEST) -o $(@)


test_soft:
	$(CXX) $(CXXFLAGS) tests/test.cc -o $(@)
	./$(@)

tricky_test: clean
	$(CXX) $(CXXFLAGS) tests/tricky_test.cc -o $(@)
	valgrind --main-stacksize=400000000  ./tricky_test


run:
	./$(EXEC)

clean:
	rm -rf $(EXEC)
	rm -rf test
	$(RM) test_soft tricky_test
