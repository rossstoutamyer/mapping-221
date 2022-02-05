#OBJ = main.o topological_sort.o # Part 2
OBJ = main.o
MAIN = main

$(MAIN): $(OBJ)
	$(CXX) -g -std=c++11 -o $(MAIN) $(OBJ)

main.o: main.cpp graph.h
	$(CXX) -g -std=c++11 -c main.cpp

topological_sort.o: topological_sort.cpp graph.h
	$(CXX) -g -std=c++11 -c topological_sort.cpp

clean: 
	rm -f $(OBJ) $(MAIN)
