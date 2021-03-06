#ifndef CELL_H
#define CELL_H

enum type { DIRT, ROOM, STONE };

class Cell
{
  bool visited;
  bool wallN, wallS, wallE, wallW;
  bool doorN, doorS, doorE, doorW;
  int type;
public :
  inline Cell();
  Cell *GetCell() { return this; }
  void Visit() { visited = true; type = DIRT;}
  inline void unVisit();
  bool isVisited() { return visited; }
  bool isWall(int dir);
  bool isDoor(int dir);
  void SetWall(int wall);
  void SetDoor(int door);
  void DelWall(int wall);
  int CountWall();
  int GetType() { return type; }
  void SetType(int type) { this->type = type; }
};

inline Cell::Cell()
{
  visited = false;
  wallS = true;
  wallN = true;
  wallE = true;
  wallW = true;
  doorN = false;
  doorS = false;
  doorE = false;
  doorW = false;
  type = STONE;
}

inline void Cell::unVisit() 
{ 
  visited = false; 
  wallN = true;
  wallS = true;
  wallE = true;
  wallW = true;
  type = STONE;
}

#endif
