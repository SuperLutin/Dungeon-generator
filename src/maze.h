#ifndef MAZE_H
#define MAZE_H
#include <list>
#include "cell.h"

enum{ NORTH, SOUTH, EAST, WEST };

typedef struct Node
{
  int x;
  int y;
}Node;

class Maze
{
  const int maxx;
  const int maxy;
  int randomness;
  int sparseness;
  int loopness;
  Cell **map;
  std::list<Node> freeCells;
  std::list<Node> deadEnd;
  int ChooseDir(int x, int y, int dir);
  int ChooseDig(int x, int y, int dir);
  void AddNodeList(int x, int y, std::list<Node> &nodelist);
  Node NewCaseInList();
  void PurgeCells();
  void DeadEndList();
  void RemoveDeadEnd();
  void DigLoop(int x, int y);
public :
  Maze(int x, int y, int randomness, int sparseness, int loopness);
  ~Maze();
  void PlaceRoom(int roomx, int roomy, int roomW, int roomH);
  bool IsCorridorInRoom(int roomx, int roomy, int roomW, int roomH);
  Cell** GetMaze() { return map; }
  int GetMaxx() { return maxx; }
  int GetMaxy() { return maxy; }
  void Dig();
  void Fill();
  void CreateLoop();
  void WriteDungeon();
};
#endif
