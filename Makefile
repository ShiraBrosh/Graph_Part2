# ID - 211821137
# GMAIL - shira1d2631@gmail.com

CXX=clang++
CXXFLAGS=-std=c++11
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp 
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run:Demo
	./$^

Demo: Demo.o $(filter-out TestCounter.o Test.o,$(OBJECTS)) 
	$(CXX) $(CXXFLAGS) $^ -o Demo

test: TestCounter.o Test.o $(filter-out Demo.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: Demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./Demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o Demo test