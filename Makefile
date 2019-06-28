CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -W -pedantic -std=c++17 -g
EXEC=soft_heap

TEST= tests/test_constructor.cpp tests/main.cpp tests/test_insert.cpp
FILE= src/main.cc

.PHONY: run


soft_heap: $(FILE)
	$(CXX) -o $(EXEC) $(FILE) $(CXXFLAGS)

test:
	$(CXX) $(CXXFLAGS) $(TEST) -o $(@)


test_soft:
	$(CXX) $(CXXFLAGS) tests/test.cc -o $(@)
	./$(@)

tricky_test:
	$(CXX) $(CXXFLAGS) tests/tricky_test.cc -o $(@)

all: $(EXEC)

run:
	./$(EXEC)

clean:
	rm -rf $(EXEC)
	rm -rf test
	$(RM) test_soft tricky_test
