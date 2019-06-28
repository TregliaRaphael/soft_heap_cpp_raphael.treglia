CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -W -pedantic -std=c++17 -g
EXEC=soft_heap tricky_test time_test test test_soft

TEST= tests/test_constructor.cpp tests/main.cpp tests/test_insert.cpp
FILE= src/main.cc


all: $(EXEC)


soft_heap: $(FILE)
	$(CXX) -o soft_heap $(FILE) $(CXXFLAGS)
	./$(@)

test: clean
	$(CXX) $(CXXFLAGS) $(TEST) -o $(@)
	./$(@)

test_soft: clean
	$(CXX) $(CXXFLAGS) tests/test.cc -o $(@)
	./$(@)

tricky_test: clean
	$(CXX) $(CXXFLAGS) tests/tricky_test.cc -o $(@)
	valgrind --main-stacksize=400000000  ./tricky_test

time_test: clean
	$(CXX) $(CXXFLAGS) tests/time_test.cc -o $(@)
	./$(@)

clean:
	rm -rf $(EXEC)
