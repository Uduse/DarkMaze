// Pragmatic Programming Competition
// 2/19/2015
// Written and organized by Russell Miller
#ifndef DARKMAZE_H
#define DARKMAZE_H

class Maze
{
  typedef struct
  { int r, c; } Pos; // position

  int** maze; // 0=wall,1=empty,2+=beenTo
  int rows;
  int cols;
  Pos p; // player
  Pos e; // exit
  int steps; // num steps taken

  bool** mtemp; // temp maze
  int** shortestPath;
  int shortestSteps;

  bool checkPossible(); // initializes mtemp, calls recursive
  bool checkPossible( int r, int c ); // recursive
  bool findShortestPath(); // finds shortest path, if possible
  void printSol(); // prints everything
  void printSol( int** maze );
  void winner();

  int sumChance( int perChance[], int index );
  void resetBackup();
  void generateMaze();
  void block( int fill );
  void spiral();
  void branching();
  void random( int fill );
  void line( int fill );
public:
  // creates and generates a maze
  // 75~150 rows
  // 60~79 columns
  // start position is in (1,1)
  // exit is in bottom right corner
  Maze( int seed );
  ~Maze();

  // returns distance to wall in specified direction
  // returns 0 if the exit is in that direction
  int lookUp();
  int lookDown();
  int lookLeft();
  int lookRight();

  // Moves player in specified direction
  // returns true if successful, false if blocked
  // increments the number of steps you've taken if successful
  // will detect if you found the exit and quit the program
  // keeps a count of how many times you visit a location up to 9
  bool goUp();
  bool goDown();
  bool goLeft();
  bool goRight();

  // prints out paths traveled with no walls
  // boundaries printed may not be walls or the edges of maze
  // this function might be useless, but it's already written
  void printPath();

  // prints the entire maze and ends the program
  void giveUp();
}; // class Maze

#endif