#ifndef ROOMGENERATOR_H
#define ROOMGENERATOR_H

#include <vector>
#include "room.h"
#include "maze.h"
#include "cell.h"

typedef struct RoomList
{
  int x;
  int y;
  int w;
  int h;
}RoomList;


class RoomGenerator
{
  int nbroom;
  std::vector<Room> rooms;
  int RoomPlaceCount(Cell **map, int x, int y, int maxx, int maxy);
 // void PlaceRoom(Cell **map, int roomx, int roomy, int maxx, int maxy);
  std::vector<RoomList> roomlist;
  void AddRoomList(int x, int y, int w, int h);
  void PlaceDoors(Cell **map, int maxx, int maxy);
  void ChooseDoor(std::list<Node> DoorNode, Cell **map, int dir);
public:
  RoomGenerator(int minnb, int maxnb, int minW, int maxW, int minH, int maxH);
  void SearchPlace(Maze &maze);
};

#endif
