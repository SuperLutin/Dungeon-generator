#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "maze.h"
#include "cell.h"

Maze::Maze(int a, int b, int c, int d, int e) : maxx(a), maxy(b)
{
  randomness = c;
  sparseness = d;
  loopness = e;

  map = new Cell*[maxx];
  for(int i = 0; i < maxx; ++i) {
    map[i] = new Cell[maxy];
  }

  std::srand(time(0));
}

Maze::~Maze()
{
  for (int i = 0; i < maxx; ++i) { 
    delete []map[i];
  }
  delete []map;
}

int Maze::ChooseDir(int x, int y, int dir)
{
  int N = 0;
  int S = 0;
  int E = 0;
  int W = 0;

  if ((x == 0) || map[x-1][y].GetCell()->isVisited())
    W = 1;
  if ((y == 0) || map[x][y-1].GetCell()->isVisited())
    N = 1;
  if ((x == (maxx - 1)) || map[x+1][y].GetCell()->isVisited())
    E = 1;
  if ((y == (maxy - 1)) || map[x][y+1].GetCell()->isVisited())
    S = 1;

  if (N == 1 &&  S == 1 && E == 1 && W == 1)
    return -1;

  int nextdir = rand()%100;
  if (nextdir < randomness) {
    if (((dir == NORTH) && !N) ||
        ((dir == SOUTH) && !S) ||
        ((dir == EAST) && !E) ||
        ((dir == WEST) && !W)) {
      return dir;
    }
  }

  dir = -1;
  do {
    nextdir = rand()%4;
    if (nextdir == NORTH && N == 0)
      dir = NORTH;
    else if (nextdir == SOUTH && S == 0)
      dir = SOUTH;
    else if (nextdir == EAST && E == 0)
      dir = EAST;
    else if (nextdir == WEST && W == 0)
      dir = WEST;
  } while (dir == -1);
  return dir;
}

int Maze::ChooseDig(int x, int y, int dir)
{
  int N = 0;
  int S = 0;
  int E = 0;
  int W = 0;

  if ((x == 0) || !map[x][y].GetCell()->isWall(WEST))
    W = 1;
  if ((y == 0) || !map[x][y].GetCell()->isWall(NORTH))
    N = 1;
  if (x == (maxx - 1) || !map[x][y].GetCell()->isWall(EAST))
    E = 1;
  if (y == (maxy - 1) || !map[x][y].GetCell()->isWall(SOUTH))
    S = 1;

  if (N == 1 &&  S == 1 && E == 1 && W == 1)
    return -1;

  int nextdir = rand()%100;
  if (nextdir < randomness) {
    if (((dir == NORTH) && !N) ||
        ((dir == SOUTH) && !S) ||
        ((dir == EAST) && !E) ||
        ((dir == WEST) && !W)) {
      return dir;
    }
  }
  dir = -1;
  do {
    nextdir = rand()%4;
    if (nextdir == NORTH && N == 0)
      dir = NORTH;
    else if (nextdir == SOUTH && S == 0)
      dir = SOUTH;
    else if (nextdir == EAST && E == 0)
      dir = EAST;
    else if (nextdir == WEST && W == 0)
      dir = WEST;
  } while (dir == -1);
  return dir;
}

Node Maze::NewCaseInList()
{
  int random = rand()%freeCells.size();
  std::list<Node>::iterator it = freeCells.begin();
  std::advance(it, random);
  return(*it);
}

void Maze::PurgeCells()
{
  std::list<Node>::iterator it = freeCells.begin();
  std::list<Node>::iterator endloop = freeCells.end();
  while (it != endloop) {
    if( ((it->x == 0)      || map[it->x - 1][it->y].GetCell()->isVisited()) &&
        ((it->x == maxx-1) || map[it->x + 1][it->y].GetCell()->isVisited()) &&
        ((it->y == 0)      || map[it->x][it->y - 1].GetCell()->isVisited()) &&
        ((it->y == maxy-1) || map[it->x][it->y + 1].GetCell()->isVisited() ) ) {
      freeCells.erase(it); break;
      endloop = freeCells.end();
    } else
      ++it;
  }
}

void Maze::AddNodeList(int x, int y, std::list<Node> &nodelist)
{
  Node node;
  node.x = x;
  node.y = y;
  nodelist.push_front(node);
}

void Maze::Dig()
{
  int x = rand()%maxx;
  int y = rand()%maxy;
  
  map[x][y].GetCell()->Visit(); 

  AddNodeList(x, y, freeCells);

  int dir = rand()%4;

  for (int count = (maxx * maxy) - 1; count > 0; --count){
    dir = ChooseDir(x, y, dir);
    switch (dir) {
      case (NORTH) :
        map[x][y].GetCell()->DelWall(NORTH);
        --y;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(SOUTH);
        AddNodeList(x, y, freeCells);
        break;
      case (SOUTH) :
        map[x][y].GetCell()->DelWall(SOUTH);
        ++y;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(NORTH);
        AddNodeList(x, y, freeCells);
        break;
      case (EAST) :
        map[x][y].GetCell()->DelWall(EAST);
        ++x;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(WEST);
        AddNodeList(x, y, freeCells);
        break;
      case (WEST) :
        map[x][y].GetCell()->DelWall(WEST);
        --x;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(EAST);
        AddNodeList(x, y, freeCells);
        break;
      default :
        //PurgeCells();
        Node tcell = NewCaseInList();
        x = tcell.x;
        y = tcell.y;
        ++count;
        break;
    }
    PurgeCells();
  }
  freeCells.clear();
}

void Maze::DeadEndList()
{
  for (int i = 0; i < maxx; i++) {
    for (int j = 0; j < maxy; j++) {
      if ( (map[i][j].GetCell()->CountWall() >= 3) &&
            map[i][j].GetCell()->isVisited())
        AddNodeList(i, j, deadEnd);
    }
  }
}

void Maze::RemoveDeadEnd()
{
  for (std::list<Node>::iterator it = deadEnd.begin(); it != deadEnd.end(); ++it) {
    map[it->x][it->y].GetCell()->unVisit();
    if (it->y != 0)
      map[it->x][it->y - 1].GetCell()->SetWall(SOUTH);
    if (it->y != (maxy-1))
      map[it->x][it->y + 1].GetCell()->SetWall(NORTH);
    if (it->x != 0)
      map[it->x - 1][it->y].GetCell()->SetWall(EAST);
    if (it->x != (maxx-1))
      map[it->x + 1][it->y].GetCell()->SetWall(WEST);
  }
}

void Maze::Fill()
{
  unsigned int sparcount = (unsigned)(sparseness * maxx * maxy) / 100;
  int ti = maxx * maxy;
  while ((unsigned)ti > sparcount) {
    DeadEndList();
    RemoveDeadEnd();
    ti = ti - deadEnd.size();
    deadEnd.clear();
  }
}

void Maze::DigLoop(int x, int y)
{
  unsigned int dir = rand()%4;
  while (map[x][y].GetCell()->CountWall() >= 3) {
    dir = ChooseDig(x, y, dir);
    switch (dir) {
      case (NORTH) :
        map[x][y].GetCell()->DelWall(NORTH);
        --y;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(SOUTH);
        break;
      case (SOUTH) :
        map[x][y].GetCell()->DelWall(SOUTH);
        ++y;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(NORTH);
        break;
      case (EAST) :
        map[x][y].GetCell()->DelWall(EAST);
        ++x;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(WEST);
        break;
      case (WEST) :
        map[x][y].GetCell()->DelWall(WEST);
        --x;
        map[x][y].GetCell()->Visit();
        map[x][y].GetCell()->DelWall(EAST);
        break;
      default :
        break;
    }
  }
}

void Maze::CreateLoop()
{
  DeadEndList();
  for (std::list<Node>::iterator it = deadEnd.begin(); it != deadEnd.end(); ++it) {
    int x = it->x;
    int y = it->y;
    if (rand()%100 < loopness)
      DigLoop(x, y);
  }
  deadEnd.clear();
}

void Maze::WriteDungeon()
{
  std::ofstream donjon("donjon", std::ios::out | std::ios::trunc);        
  if (donjon) {
    donjon << ' ' ;
    for (int i = 0; i != maxx; ++i) {
      donjon << "_ " ;
    }
    donjon << '\n';

    for (int j = 0; j != maxy; ++j) {
      donjon << '|';
      for (int i = 0; i != maxx; ++i) {
        if (map[i][j].GetCell()->isVisited()) {
          if (map[i][j].GetCell()->isWall(SOUTH))
            donjon << '_';
          else if (map[i][j].GetCell()->isDoor(SOUTH))
             donjon << ' ';
          else
            donjon << ' '; 
          if (map[i][j].GetCell()->isWall(EAST))
            donjon << '|';
          else if (map[i][j].GetCell()->isDoor(EAST))
             donjon << ' ';
          else
            donjon << ' '; 
        }// else if (map[i][j].GetCell()->GetType() == ROOM)
          //donjon << "OO"; 
        else
          donjon << "X|"; 
      }
      donjon << '\n';
    }

    donjon.close();
  } else {
    std::cerr << "Erreur à l'ouverture !" << std::endl;
  }
}

void Maze::PlaceRoom(int roomx, int roomy, int roomW, int roomH)
{

  for (int i = roomx; i < roomx+roomW; ++i) {
    for (int j = roomy; j < roomy+roomH; ++j) {
      map[i][j].Visit();
      map[i][j].SetType(ROOM);
      map[i][j].DelWall(NORTH);
      map[i][j].DelWall(SOUTH);
      map[i][j].DelWall(EAST);
      map[i][j].DelWall(WEST);

      if ( i == roomx)
        map[i][j].SetWall(WEST);
      else if ( i == roomx + roomW - 1 )
        map[i][j].SetWall(EAST);
      if ( j == roomy)
        map[i][j].SetWall(NORTH);
      else if ( j == roomy + roomH - 1)
        map[i][j].SetWall(SOUTH);

      if (i != 0 && i == roomx)
        map[i-1][j].SetWall(EAST);
      else if (i != maxx-1 && i == roomx+roomW-1) 
        map[i+1][j].SetWall(WEST);
      if (j != 0 && j == roomy)
        map[i][j-1].SetWall(SOUTH);
      else if (j != maxy-1 && j == roomy+roomH-1) 
        map[i][j+1].SetWall(NORTH);
    }
  }
}

bool Maze::IsCorridorInRoom(int roomx, int roomy, int roomW, int roomH)
{
for (int i = 0; i < roomW; ++i) {
for(int j=0;j<roomH;++j){
      if (map[roomx+i][roomy+j].GetCell()->GetType() == DIRT)
        return true;
    }
  }
  return false;
}
