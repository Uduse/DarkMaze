#ifndef MAZE_SOLVER
#define MAZE_SOLVER

#include <iostream>
#include <cstdlib>
#include "darkMaze.h"
#include <vector>
#include <stack>

using namespace std;

#define MAX_ROWS 150
#define MAX_COLS 80

#define LOOK_MAX 10000

#define DOWN 0
#define RIGHT 1
#define UP 2
#define LEFT 3 

#define RIGHT_PRIORITY 3

// Facing
// 0 down
// 1 right
// 2 up
// 3 left

struct Block
{
	int x;
	int y;
	int mark;

	Block():mark( 0 )
	{

	}

public:
	void set( int i, int j )
	{
		x = i;
		y = j;
	}

};

class MazeSolver
{
private:
	Maze* m;

	int row;
	int col;

	int facing;

	Block** map;
	//Maze* myMaze;

public:
	MazeSolver( Maze* maze_ ): m( maze_ ), row( 1 ), col( 1 ), facing( 0 )
	{
		map = new Block*[MAX_ROWS];
		for ( int i = 0; i < MAX_ROWS; i++ )
		{
			map[i] = new Block[MAX_COLS];
			for ( int j = 0; j < MAX_COLS; j++ )
			{
				map[i][j].set( i, j );
			}
		}

	}

	void markHere()
	{
		map[row][col].mark++;
	}

	bool goForward()
	{
		switch ( facing )
		{
		case 0:
			if ( m->goDown() )
			{
				row++;
				return true;
			}
			return false;
			break;
		case 1:
			if ( m->goRight() )
			{
				col++;
				return true;
			}
			return false;
			break;
		case 2:
			if ( m->goUp() )
			{
				row--;
				return true;
			}
			return false;
			break;
		case 3:
			if ( m->goLeft() )
			{
				col--;
				return true;
			}
			return false;
			break;
		default:
			break;
		}
		return false;
	}

	void turnCounterClockwise()
	{
		facing = facing + 1;
		facing %= 4;
	}

	void turnClockwise()
	{
		facing--;
		if ( facing < 0 )
		{
			facing = 3;
		}
	}

	void goRightHand()
	{
		turnClockwise();
		if ( !goForward() )
		{
			turnCounterClockwise();
			if ( !goForward() )
			{
				turnCounterClockwise();
				if ( !goForward() )
				{
					turnCounterClockwise();
					goForward();
					return;
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
		return;
	}

	void goLeftHand()
	{
		turnCounterClockwise();
		if ( !goForward() )
		{
			turnClockwise();
			if ( !goForward() )
			{
				turnClockwise();
				if ( !goForward() )
				{
					turnClockwise();
					goForward();
					return;
				}
				else
				{
					return;
				}
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
		return;
	}

	void solve()
	{
		int option = 2;
		//option = rand() % 3 + 1;
		facing = 0;


		switch ( option )
		{

			//==================//
			//  T1
			//==================//

		case 1:
			while ( true )
			{
				goRightHand();
			}
			break;

			//==================//
			//  T2
			//==================//

		case 2:
			while ( true )
			{
				goLeftHand();
			}
			break;

			//==================//
			//  T3
			//==================//

		case 3:
			DFS();
			break;
		default:
			break;
		}
		m->printPath();
	}

	int getMark( int direction )
	{
		int downRow = row + 1;
		int rightCol = col + 1;
		int upRow = row - 1;
		int leftCol = col - 1;

		//cout << "downRow: " << downRow << endl;
		//cout << "rightCol: " << rightCol << endl;
		//cout << "upRow: " << upRow << endl;
		//cout << "leftCol: " << leftCol << endl;
		//cout << endl;

		switch ( direction )
		{
		case 0:
			// if not a wall
			if ( m->lookDown() != 1 )
			{
				return map[downRow][col].mark;
			}
			else
			{
				return LOOK_MAX;
			}
		case 1:
			if ( m->lookRight() != 1 )
			{
				return map[row][rightCol].mark;
			}
			else
			{
				return LOOK_MAX;
			}
		case 2:
			if ( m->lookUp() != 1 )
			{
				return map[upRow][col].mark;
			}
			else
			{
				return LOOK_MAX;
			}
		case 3:
			if ( m->lookLeft() != 1 )
			{
				return map[row][leftCol].mark;
			}
			else
			{
				return 10;
			}
		default:
			break;
		}
		return 0;
	}

	void goDFS()
	{
		int downMark = getMark( DOWN );
		int rightMark = getMark( RIGHT );
		int upMark = getMark( UP );
		int leftMark = getMark( LEFT );
		int minMark = min( min( downMark, rightMark ), min( leftMark, upMark ) );
		//cout << "downMark: " << downMark << endl;
		//cout << "rightMark: " << rightMark << endl;
		//cout << "upMark: " << upMark << endl;
		//cout << "leftMark : " << leftMark << endl;
		//cout << "maxMark: " << minMark << endl;
		//cout << endl;

		int maxMark = max( max( downMark, rightMark ), max( leftMark, upMark ) );

		if ( true )
		{

		}

		if ( downMark == minMark && rightMark == minMark )
		{
			if ( rand() % RIGHT_PRIORITY == 0 )
			{
				facing = DOWN;
				goForward();
			}
			else
			{
				facing = RIGHT;
				goForward();
			}
			return;
		}

		if ( downMark == minMark )
		{
			facing = DOWN;
			goForward();
		}
		else if ( rightMark == minMark )
		{
			facing = RIGHT;
			goForward();
		}
		else if ( upMark == minMark )
		{
			facing = UP;
			goForward();
		}
		else
		{
			facing = LEFT;
			goForward();
		}

	}

	void DFS()
	{

		markHere();
		while ( true )
		{
			//cout << "row: " << row << endl;
			//cout << "col: " << col << endl;

			goDFS();
			markHere();
			//m->printPath();
			//cin.get();
		}
	}

	// solve()
}; // class MazeSolver


// Can write more functions here if you want!


#endif