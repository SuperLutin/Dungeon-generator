#include <cstdlib>
#include <vector>
#include <list>
#include "roomgenerator.h"
#include "room.h"
#include "maze.h"
#include "cell.h"

RoomGenerator::RoomGenerator(int minnb, int maxnb,
                             int minW, int maxW,
                             int minH, int maxH)
{
  nbroom = rand()%maxnb + minnb;
  for (int i = 0; i != nbroom; ++i) {
    rooms.push_back(Room(minW, maxW, minH, maxH));
  }
}

int RoomGenerator::RoomPlaceCount(Cell **map, int x, int y, int maxx, int maxy)
{
  int val = 0;
  switch (map[x][y].GetCell()->GetType()) {
    case DIRT:
      ++val; ++val; ++val;
      break;
    case ROOM:
      val += 100;
      break;
    case STONE:
      break;
  }
  if (x != maxx-1) {
    if (map[x+1][y].GetCell()->GetType() == DIRT)
      ++val;
    else if (map[x+1][y].GetCell()->GetType() == ROOM)
      val += 20;
  } else val += 10;
  if (x != 0) {
    if (map[x-1][y].GetCell()->GetType() == DIRT)
        ++val;
    else if (map[x-1][y].GetCell()->GetType() == ROOM)
      val += 20;
  } else val += 10;
  if (y != maxy-1) {
    if (map[x][y+1].GetCell()->GetType() == DIRT)
        ++val;
    else if (map[x][y+1].GetCell()->GetType() == ROOM)
      val += 20;
  } else val += 10;

  if (y != 0) {
    if (map[x][y-1].GetCell()->GetType() == DIRT)
        ++val;
    else if (map[x][y-1].GetCell()->GetType() == ROOM)
      val += 100;
  } else val += 11;
  return val;
} 

void RoomGenerator::SearchPlace(Maze &maze)
{
  int maxx = maze.GetMaxx();
  int maxy = maze.GetMaxy();
  std::list<Node>listrooms;
  Node node; node.x = 0; node.y = 0;

  while (!rooms.empty()) {
    listrooms.clear();
    int roomW = rooms.front().GetRoomW();
    int roomH = rooms.front().GetRoomH();
    int val = maxx * maxy * 1000;
    int curval = 0;
    for (int x = 0; x <= (maxx - rooms.begin()->GetRoomW()); ++x) {
      for (int y = 0; y <= (maxy - rooms.begin()->GetRoomH()); ++y) {
        curval = 0;
        for ( int i = 0; i < roomW ; ++i) {
          for ( int j = 0; j < roomH ; ++j) {
            curval += RoomPlaceCount(maze.GetMaze(), i+x, j+y, maxx, maxy);
          }
        }
        if (curval < val) {
          node.x = x;
          node.y = y;
          if (maze.IsCorridorInRoom(node.x, node.y, roomW, roomH)) {
            listrooms.clear();
            val = curval;
            listrooms.push_front(node);
          }
        } else if (curval == val) {
          node.x = x;
          node.y = y;
          if (maze.IsCorridorInRoom(node.x, node.y, roomW, roomH)) {
            val = curval;
            listrooms.push_front(node);
          }
        }
      }
    }
    if (val != maxx * maxy * 1000) {
      int n = rand() % listrooms.size();
      std::list<Node>::iterator it = listrooms.begin();
      std::advance(it, n);
      maze.PlaceRoom(it->x, it->y, roomW, roomH);
      listrooms.clear();
      rooms.erase(rooms.begin());
    }
  }
  rooms.clear();
}
