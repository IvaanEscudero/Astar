# Uncomment one of this to compile the program with each heuristis
# Non-informative
CHOICE=ni
# CHOICE=euclidea
# CHOICE=manhattan

CHOSEN_H=${CHOICE}_HEURISTIC

Astar: Astar.cpp Maze.o heuristic.o
	g++ -Wall Maze.o heuristic.o Astar.cpp -o Astar
	mv Astar Astar_${CHOICE}

Maze.o: Maze.cpp Maze.h
	g++ -Wall -c Maze.cpp

heuristic.o: heuristic.cpp heuristic.h
	g++ -Wall -D${CHOSEN_H} -c heuristic.cpp

# Removes the objects
clean:
	-rm *.o

# Removes the executables, too
allclean:
	-rm *.o
	-rm Astar_*
