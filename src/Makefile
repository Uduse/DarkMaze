darkMaze.out: darkMaze.o darkMazeSolver.o
	g++ -Wall -g -o darkMaze.out darkMaze.o darkMazeSolver.o

darkMaze.o: darkMaze.cpp darkMaze.h darkMazeSolver.cpp
	g++ -Wall -g -c darkMaze.cpp

darkMazeSolver.o: darkMazeSolver.cpp
	g++ -Wall -g -c darkMazeSolver.cpp

clean:
	rm -f *.o core darkMaze.out