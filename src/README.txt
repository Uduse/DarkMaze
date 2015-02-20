Pragmatic Programming Maze Solving Competition
2/19/2015
Written and organized by Russell Miller

Welcome to Pragmatic Programming!

Today's competition will be to traverse a maze, finding the exit.
The goal is to find the exit in as few steps as possible.
You will have roughly 2~2.5 hours to complete your program.
Good Luck!

About the program:
A maze is generated using a seed in the file darkMaze.cpp and darkMaze.h and stored internally in the Maze class. A MazeSolver object is then created, and the function solve() is called. Your solver should be written inside the solve() function in the file darkMazeSolver.cpp
There is more detailed information about the program written inside darkMaze.h
The maze generation code is also viewable inside darkMaze.cpp


Maze Traversal:
You can move about the maze using the four functions:
m->goUp();
m->goDown();
m->goLeft();
m->goRight();
They will move you 1 step in the specified direction.

Other features:
You have something similar to a radar with the four functions:
m->lookUp();
m->lookDown();
m->lookLeft();
m->lookRight();
These allow you to look in the specified direction without actually moving in that direction. They will return the distance to the nearest wall in that direction.

To prevent infinite loops, there is a backup function to end the program:
m->giveUp();

Warning:
There are some pathfinding algorithms that require omniscience of the maze. Have caution with these since you won't have omniscience with this program.


*** Rules: ***
The only file allowed to be modified is darkMazeSolver.cpp
The method of submission will be handin in CSIF:
handin blahs15 darkMaze darkMazeSolver.cpp
The other files will be copied into your handin directory and compiled and run.
Everyone's program will be tested using multiple seeds, and the sum of the steps your program makes will be added together to determine the winner.


Prize for winning:
The winner will receive a Davis Computer Science Club T-shirt for free when they arrive in the mail.
