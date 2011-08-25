#ifndef ROOMGENERATOR_H
#define ROOMGENERATOR_H

#include <vector>
#include "room.h"
#include "maze.h"
#include "cell.h"

class RoomGenerator
{
  int nbroom;
  std::vector<Room> rooms;
  int RoomPlaceCount(Cell **map, int x, int y, int maxx, int maxy);
 // void PlaceRoom(Cell **map, int roomx, int roomy, int maxx, int maxy);
public:
  RoomGenerator(int minnb, int maxnb, int minW, int maxW, int minH, int maxH);
  void SearchPlace(Maze &maze);
};

#endif
