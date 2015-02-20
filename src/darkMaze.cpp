// Pragmatic Programming Competition
// 2/19/2015
// Written and organized by Russell Miller

#include <iostream>
#include <cstdlib>
#include <queue>
#include "darkMaze.h"
#include "darkMazeSolver.cpp"
#include "Escape_Sequence_Colors.h"

using namespace std;

int main()
{
  int seed;
  cout << "input seed > ";
  cin >> seed;
  Maze* maze = new Maze(seed);
  
  MazeSolver solver(maze);
  solver.solve();
  maze->giveUp();
} // main()


Maze::Maze( int seed ) : steps(0), shortestPath(0)
{
  srand( seed );
  rows = rand() % 76 + 75; // 75~150 rows
  cols = rand() % 20 + 60; // 60~79 cols
  // cout << "rows: " << rows << endl;
  // cout << "cols: " << cols << endl;

  // allocation
  maze = new int*[rows];
  for( int i = 0; i < rows; i++ )
  {
    maze[i] = new int[cols];
    for( int k = 0; k < cols; k++ )
      maze[i][k] = 1;
  } // for each row

  // start, end initialization
  p.r = 1;
  p.c = 1;
  e.r = rows-2;
  e.c = cols-2;

  // edge initialization
  for( int i = 0; i < rows; i++ )
  {
    maze[i][0] = 0;
    maze[i][cols-1] = 0;
  } // for rows
  for( int k = 1; k < cols-1; k++ )
  {
    maze[0][k] = 0;
    maze[rows-1][k] = 0;
  } // for cols

  // initialize maze walls
  generateMaze();
  findShortestPath();
  printSol( shortestPath );

  maze[p.r][p.c] = 2; // beenTo first spot
  maze[e.r][e.c] = 1; // exit not a wall
} // Maze constructor

Maze::~Maze()
{
  if( maze )
  {
    for( int i = 0; i < rows; i++ )
      delete maze[i];
    delete maze;
  } // if maze
  if( shortestPath )
  {
    for( int i = 0; i < rows; i++ )
      delete shortestPath[i];
    delete shortestPath;
  } // if shortestPath
} // Maze deconstructor


bool Maze::checkPossible()
{
  mtemp = new bool*[rows];
  for( int i = 0; i < rows; i++ )
  {
    mtemp[i] = new bool[cols];
    for( int k = 0; k < cols; k++ )
    {
      if( !maze[i][k] )
        mtemp[i][k] = false; // wall
      else
        mtemp[i][k] = true; // not wall
    } // cols
  } // rows
  bool possible = checkPossible( p.r, p.c );
  for( int i = 0; i < rows; i++ )
    delete mtemp[i];
  delete mtemp;
  return possible;
} // checkPossible()
bool Maze::checkPossible( int r, int c )
{ // search order: down, right, left, up
  // returns true if path is found
  if( r == e.r && c == e.c )
    return true; // exit found
  if( false == mtemp[r][c] )
    return false; // wall found
  mtemp[r][c] = false; // set to 'wall'
  if( checkPossible( r+1, c ) )
    return true; // down
  if( checkPossible( r, c+1 ) )
    return true; // right
  if( checkPossible( r, c-1 ) )
    return true; // left
  if( checkPossible( r-1, c ) )
    return true; // up
  return false; // no path found
} // checkPossible(r,c)


int Maze::lookUp()
{
  int distance = 0;
  for( int i = p.r; maze[i][p.c]; i-- )
  {
    if( i == e.r && p.c == e.c )
      return 0; // exit found
    distance++;
  } // for up
  return distance;
} // lookUp()
int Maze::lookDown()
{
  int distance = 0;
  for( int i = p.r; maze[i][p.c]; i++ )
  {
    if( i == e.r && p.c == e.c )
      return 0; // exit found
    distance++;
  } // for down
  return distance;
} // lookDown()
int Maze::lookLeft()
{
  int distance = 0;
  for( int k = p.c; maze[p.r][k]; k-- )
  {
    if( p.r == e.r && k == e.c )
      return 0; // exit found
    distance++;
  } // for left
  return distance;
} // lookLeft()
int Maze::lookRight()
{
  int distance = 0;
  for( int k = p.c; maze[p.r][k]; k++ )
  {
    if( p.r == e.r && k == e.c )
      return 0; // exit found
    distance++;
  } // for left
  return distance;
} // lookRight()


bool Maze::goUp()
{
  if( !maze[p.r-1][p.c] )
    return false; // can't move up
  p.r--;
  steps++;
  if( p.r == e.r && p.c == e.c )
    winner();
  maze[p.r][p.c]++;
  if( maze[p.r][p.c] > 10 )
    maze[p.r][p.c] = 10;
  return true;
} // goUp()
bool Maze::goDown()
{
  if( !maze[p.r+1][p.c] )
    return false; // can't move up
  p.r++;
  steps++;
  if( p.r == e.r && p.c == e.c )
    winner();
  maze[p.r][p.c]++;
  if( maze[p.r][p.c] > 10 )
    maze[p.r][p.c] = 10;
  return true;
} // goDown()
bool Maze::goLeft()
{
  if( !maze[p.r][p.c-1] )
    return false; // can't move up
  p.c--;
  steps++;
  if( p.r == e.r && p.c == e.c )
    winner();
  maze[p.r][p.c]++;
  if( maze[p.r][p.c] > 10 )
    maze[p.r][p.c] = 10;
  return true;
} // goLeft()
bool Maze::goRight()
{
  if( !maze[p.r][p.c+1] )
    return false; // can't move up
  p.c++;
  steps++;
  if( p.r == e.r && p.c == e.c )
    winner();
  maze[p.r][p.c]++;
  if( maze[p.r][p.c] > 10 )
    maze[p.r][p.c] = 10;
  return true;
} // goRight()


void Maze::giveUp()
{
  printSol();
  exit(0);
} // giveUp()
void Maze::winner()
{
  printSol();
  cout << "YOU FOUND THE EXIT!" << endl;
  exit(0);
} // winner()

void Maze::printPath()
{
  // find traveled edges
  int farUp = rows, farDown = 0, farLeft = cols, farRight = 0;
  for( int i = 0; i < rows; i++ )
  {
    for( int k = 0; k < cols; k++ )
    {
      if( i < farUp && maze[i][k] >= 2 )
        farUp = i;
      if( i > farDown && maze[i][k] >= 2 )
        farDown = i;
      if( k < farLeft && maze[i][k] >= 2 )
        farLeft = k;
      if( k > farRight && maze[i][k] >= 2 )
        farRight = k;
    } // for cols
  } // for rows
  // cout << "up: " << farUp << " down: " << farDown << endl;
  // cout << "left: " << farLeft << " right: " << farRight << endl;

  cout << COLOR_BLACK_BLACK << "+";
  for( int k = farLeft; k <= farRight; k++ )
    cout << "-";
  cout << "+" << COLOR_NORMAL << endl;

  for( int i = farUp; i <= farDown; i++ )
  {
    cout << COLOR_BLACK_BLACK << "|" << COLOR_NORMAL;
    for( int k = farLeft; k <= farRight; k++ )
    {
      if( i == p.r && k == p.c )
        cout << COLOR_GREEN_YELLOW << "P" << COLOR_NORMAL; // player
      else if( 2 <= maze[i][k] )
        cout << COLOR_CYAN_BLACK << maze[i][k] - 1 << COLOR_NORMAL; // visit #
      else // unvisited, wall, exit
        cout << COLOR_BLACK_BLACK << " " << COLOR_NORMAL; // unvisited
    }
    cout << COLOR_BLACK_BLACK << "|" << COLOR_NORMAL << endl;
  } // for rows

  cout << COLOR_BLACK_BLACK << "+";
  for( int k = farLeft; k <= farRight; k++ )
    cout << "-";
  cout << "+" << COLOR_NORMAL << endl;

  cout << "Steps taken: " << steps << endl;
} // printPath()

void Maze::printSol()
{ printSol( maze ); }
void Maze::printSol( int** m )
{
  for( int i = 0; i < rows; i++ )
  {
    for( int k = 0; k < cols; k++ )
    {
      if( i == p.r && k == p.c && p.r == e.r && p.c == e.c )
        cout << COLOR_BLACK_GREEN << "W" << COLOR_NORMAL; // winner
      else if( i == p.r && k == p.c )
        cout << COLOR_GREEN_YELLOW << "P" << COLOR_NORMAL; // player
      else if( i == e.r && k == e.c )
        cout << COLOR_BLACK_CYAN << "E" << COLOR_NORMAL; // exit
      else if( !m[i][k] ) // wall
      {
        cout << COLOR_MAGENTA_BLACK;
        if( (i && !m[i-1][k]) || (i != rows-1 && !m[i+1][k]) )
        {
          if( (k && !m[i][k-1]) || (k != cols-1 && !m[i][k+1]) )
            cout << "+"; // walls up|down & left|right
          else
            cout << "|"; // walls up|down
        } // wall up|down
        else if( (k && !m[i][k-1]) || (k != cols-1 && !m[i][k+1]) )
          cout << "-"; // walls left|right
        else
          cout << "X";
        cout << COLOR_NORMAL;
      } // if wall
      else if( 1 == m[i][k] )
        cout << COLOR_BLACK_BLACK << " " << COLOR_NORMAL; // unvisited
      else // if( 2 <= m[i][k] )
        cout << COLOR_CYAN_BLACK << m[i][k]-1 << COLOR_NORMAL; // visit #
    } // for cols
    cout << endl;
  } // for rows
  cout << "Optimal steps: " << shortestSteps << endl;
  cout << "Steps taken: " << steps << endl;
} // printSol()


bool Maze::findShortestPath()
{
  int max = rows * cols;
  if( shortestPath )
  {
    for( int i = 0; i < rows; i++ )
      delete shortestPath[i];
    delete shortestPath;
  } // if initiated
  shortestPath = new int*[rows];
  for( int i = 0; i < rows; i++ )
  {
    shortestPath[i] = new int[cols];
    for( int k = 0; k < cols; k++ )
    {
      if( maze[i][k] )
        shortestPath[i][k] = max; // empty
      else
        shortestPath[i][k] = 0; // wall
    } // cols
  } // for rows

  shortestPath[p.r][p.c] = 1; // start count
  queue<Pos> locs; // locations
  Pos p2; // p2 = start pos
  p2.r = p.r;
  p2.c = p.c;
  locs.push(p2); // push start pos

  while( !locs.empty() ) // empty => path not found
  {
    int r = locs.front().r;
    int c = locs.front().c;
    int count = shortestPath[r][c];
    if( r == e.r && c == e.c )
      break; // exit found

    // down, right, left, up
    // don't need to check for walls since they are < count
    if( shortestPath[r+1][c] > count + 1 || (r+1 == e.r && c == e.c) )
    {
      shortestPath[r+1][c] = count + 1;
      p2.r = r+1;
      p2.c = c;
      locs.push(p2);
    } // if down
    if( shortestPath[r][c+1] > count + 1 || (r == e.r && c+1 == e.c) )
    {
      shortestPath[r][c+1] = count + 1;
      p2.r = r;
      p2.c = c+1;
      locs.push(p2);
    } // if right
    if( shortestPath[r][c-1] > count + 1 || (r == e.r && c-1 == e.c) )
    {
      shortestPath[r][c-1] = count + 1;
      p2.r = r;
      p2.c = c-1;
      locs.push(p2);
    } // if left
    if( shortestPath[r-1][c] > count + 1 || (r-1 == e.r && c == e.c) )
    {
      shortestPath[r-1][c] = count + 1;
      p2.r = r-1;
      p2.c = c;
      locs.push(p2);
    } // if up
    locs.pop();
  } // while finding path

  if( !locs.empty() )
  {
    int r = locs.front().r;
    int c = locs.front().c;
    shortestSteps = shortestPath[r][c] - 1;
    int count = shortestPath[r][c] - 1;
    while( r != p.r || c != p.c )
    {
      // left, up, right, down
      if( count == shortestPath[r][c-1] )
        c--; // if up
      else if( count == shortestPath[r-1][c] )
        r--; // if left
      else if( count == shortestPath[r][c+1] )
        c++; // if right
      else if( count == shortestPath[r+1][c] )
        r++; // if down
      count = shortestPath[r][c] - 1;
      shortestPath[r][c] = -2;
    } // while going back to start

    for( int i = 0; i < rows; i++ )
      for( int k = 0; k < cols; k++ )
      {
        if( 0 < shortestPath[i][k] )
          shortestPath[i][k] = 1;
        else if( -2 == shortestPath[i][k] )
          shortestPath[i][k] = 2;
      } // for cols

    // printSol( shortestPath );
    return true;
  } // if exit found

  // cout << "no path found" << endl;
  return false;
} // findShortestPath()

int Maze::sumChance( int perChance[], int index )
{
  int sum = 0;
  for( int i = 0; i < index + 1; i++ )
    sum += perChance[i];
  return sum;
} // sumChance()

void Maze::resetBackup()
{
  for( int i = 0; i < rows; i++ )
  {
    for( int k = 0; k < cols; k++ )
    {
      if( !maze[i][k] )
        mtemp[i][k] = false; // wall
      else
        mtemp[i][k] = true; // not wall
    } // cols
  } // rows
} // createTemp()

void Maze::generateMaze()
{
  mtemp = new bool*[rows]; // backup of previous walls
  for( int i = 0; i < rows; i++ )
    mtemp[i] = new bool[cols];

  int perChance[8] = { 
  // if add options, change "int r = rand()" line
  25, // 0 block
  15, // 1 empty block
  15, // 2 spiral
  45, // 3 random
  20, // 4 empty random
  30, // 5 random branching
  50, // 6 line
  35, // 7 empty line
  }; // percentage chance of each option

  int numRuns = rows * 1.3; // run # generation functions
  for( int i = 0; i < numRuns; i++ )
  {
    resetBackup();
    int r = rand() % sumChance(perChance, 7); // perChance.len - 1
    if( r < sumChance(perChance, 0) )
      block(0); // if block
    else if( r < sumChance(perChance, 1) )
      block(1); //if empty block
    else if( r < sumChance(perChance, 2) )
      spiral(); // if spiral
    else if( r < sumChance(perChance, 3) )
      random( 0 ); // if random
    else if( r < sumChance(perChance, 4) )
      random( 1 ); // if empty random
    else if( r < sumChance(perChance, 5) )
      branching(); // if random branching
    else if( r < sumChance(perChance, 6) )
      line( 0 ); // if line
    else if( r < sumChance(perChance, 7) )
      line( 1 ); // if line

    if( !findShortestPath() )
    { // revert
      // cout << "revert" << endl;
      for( int i = 0; i < rows; i++ )
        for( int k = 0; k < cols; k++ )
        {
          if( !mtemp[i][k] && maze[i][k] ) // wall && empty
            maze[i][k] = 0;
          else if( mtemp[i][k] && !maze[i][k] ) // empty && wall
            maze[i][k] = 1;
        } // for
    } // if made impossible
  } // for

  for( int i = 0; i < rows; i++ )
    delete mtemp[i];
  delete mtemp;
} // generateMaze()

void Maze::block( int fill )
{
  int width = rand() % 5 + 3; // 3~7
  Pos start;
  start.r = (rand() % (rows-2) + 1) - width/2;
  start.c = (rand() % (cols-2) + 1) - width/2;

  for( int i = 0; i < width; i++ )
  {
    if( 1 > i+start.r || i+start.r >= rows-1 )
      continue; // out of bounds
    for( int k = 0; k < width; k++ )
    {
      if( 1 > k+start.c || k+start.c >= cols-1 )
        continue; // out of bounds
      if( i+k >= width*2/4 && i+k < width*2*3/4 && i-k <= width/2 && k-i <= width/2)
        maze[i+start.r][k+start.c] = 0;
    } // for cols 
  } // for rows
} // block()

void Maze::spiral()
{
  /*
  X                 X
  X                 X
  X XXXXXXX XXXXXXX X
  X X     X X     X X
  X X XXX X X XXX X X
  X X X X X X X X X X
  X X   X X X X   X X
  X XXXXX X X XXXXX X
  X       X X       X
  XXXXXXXXX XXXXXXXXX
  */
  bool clockwise = rand() % 2;
  int height = (rand() % 3 + 10) * 3/2;
  int dir = rand() % 4;
  int extension = rand() % 7 + 3;
  Pos start;
  // initiate starting Pos
  if( clockwise )
  {
    if( 0 == dir ) // <-
    {
      start.r = rand() % (rows-(height+1)) + height+1;
      start.c = rand() % (cols-(height+1)) + height+1;
    } // if left
    else if( 1 == dir ) // up
    {
      start.r = rand() % (rows-(height+1)) + height+1;
      start.c = rand() % (cols-(height+1));
    } // if up
    else if( 2 == dir ) // ->
    {
      start.r = rand() % (rows-(height+1));
      start.c = rand() % (cols-(height+1));
    } // if right
    else if( 3 == dir ) // down
    {
      start.r = rand() % (rows-(height+1));
      start.c = rand() % (cols-(height+1)) + height+1;
    } // if down
  } // if clockwise
  else // counterclockwise
  {
    if( 0 == dir ) // <-
    {
      start.r = rand() % (rows-(height+1));
      start.c = rand() % (cols-(height+1)) + height+1;
    } // if left
    else if( 1 == dir ) // up
    {
      start.r = rand() % (rows-(height+1)) + height+1;
      start.c = rand() % (cols-(height+1)) + height+1;
    } // if up
    else if( 2 == dir ) // ->
    {
      start.r = rand() % (rows-(height+1)) + height+1;
      start.c = rand() % (cols-(height+1));
    } // if right
    else if( 3 == dir ) // down
    {
      start.r = rand() % (rows-(height+1));
      start.c = rand() % (cols-(height+1));
    } // if down
  } // else counterclockwise

  // extensions
  if( 0 == dir ) // <-
    for( int k = start.c; k < start.c + extension; k++ )
    {
      if( k >= cols )
        break;
      maze[start.r][k] = 0;
    } // for extension
  else if( 1 == dir ) // up
    for( int i = start.r; i < start.r + extension; i++ )
    {
      if( i >= rows )
        break;
      maze[i][start.c] = 0;
    } // for extension
  else if( 2 == dir ) // ->
    for( int k = start.c; k >= start.c - extension; k-- )
    {
      if( k < 0 )
        break;
      maze[start.r][k] = 0;
    } // for extension
  else if( 3 == dir ) // down
    for( int i = start.r; i >= start.r - extension; i-- )
    {
      if( i < 0 )
        break;
      maze[i][start.c] = 0;
    } // for extension

  // create spiral
  while( height > 1 )
  {
    switch(dir)
    {
      case 0: // left
        for( int k = 0; k < height; k++ )
          maze[start.r][start.c-k] = 0;
        height--;
        start.c -= height;
        break;
      case 1: // up
        for( int i = 0; i < height; i++ )
          maze[start.r-i][start.c] = 0;
        height--;
        start.r -= height;
        break;
      case 2: // right
        for( int k = 0; k < height; k++ )
          maze[start.r][start.c+k] = 0;
        height--;
        start.c += height;
        break;
      case 3: // down
        for( int i = 0; i < height; i++ )
          maze[start.r+i][start.c] = 0;
        height -= 2;
        start.r += height;
        break;
    } // switch(dir)
    
    if( clockwise )
    {
      dir++;
      if( dir == 4 )
        dir = 0;
    } // if clockwise
    else
    {
      dir--;
      if( dir == -1 )
        dir = 3;
    } // else counterclockwise
  } // while
} // spiral()


void Maze::branching()
{
  Pos temp;
  temp.r = rand() % (rows-2) + 1;
  temp.c = rand() % (cols-2) + 1;
  int chances = 2;
  queue<Pos> nodes;
  nodes.push(temp);
  while( !nodes.empty() )
  {
    Pos cur = nodes.front();
    if( cur.r <= 0 || cur.r >= rows-1 || cur.c <= 0 || cur.c >= cols-1 )
    { // edge --> stop
      nodes.pop();
      continue;
    }
    maze[cur.r][cur.c] = 0; // wall
    if( !(rand() % (chances/2)) )
    {
      temp.r = cur.r - 2;
      temp.c = cur.c;
      if( (temp.r > 0 && maze[temp.r][temp.c]) || 0 == temp.r)
      {
        maze[cur.r-1][cur.c] = 0;
        nodes.push(temp);
      }
    } // if up
    if( !(rand() % (chances/2)) )
    {
      temp.r = cur.r + 2;
      temp.c = cur.c;
      if( (temp.r < rows-1 && maze[temp.r][temp.c]) || rows-1 == temp.r)
      {
        maze[cur.r+1][cur.c] = 0;
        nodes.push(temp);
      }
    } // if down
    if( !(rand() % (chances/2)) )
    {
      temp.r = cur.r;
      temp.c = cur.c - 2;
      if( (temp.c > 0 && maze[temp.r][temp.c]) || 0 == temp.c)
      {
        maze[cur.r][cur.c-1] = 0;
        nodes.push(temp);
      }
    } // if left
    if( !(rand() % (chances/2)) )
    {
      temp.r = cur.r;
      temp.c = cur.c + 2;
      if( (temp.c < cols-1 && maze[temp.r][temp.c]) || cols-1 == temp.c)
      {
        maze[cur.r][cur.c+1] = 0;
        nodes.push(temp);
      }
    } // if right
    // if( chances < 20 )
      chances++;
    nodes.pop();
  } // while keep branching
} // branching()


void Maze::random( int fill )
{
  int count = rand() % 25 + 15;
  for( int i = 0; i < count; i++ )
  {
    int r = rand() % (rows-2) + 1;
    int c = rand() % (cols-2) + 1;
    maze[r][c] = fill;
  } // for count
} // random()


void Maze::line( int fill )
{
  int r = rand() % rows;
  int c = rand() % cols;
  int dir = rand() % 4;
  int length = rand() % 11 + 10; // 10~20

  for( int i = 0; i < length; i++ )
  {
    if( r <= 0 || r >= rows - 1 || c <= 0 || c >= cols-1 )
      continue;
    maze[r][c] = fill;
    switch(dir)
    {
      case 0: // left
        c--;
        break;
      case 1: // right
        c++;
        break;
      case 2: // up
        r--;
        break;
      case 3: // down
        r++;
        break;
    } // switch(dir)
  } // for
} // line()


