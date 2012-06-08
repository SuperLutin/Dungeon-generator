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
  if (maxnb == 0)
  {
    nbroom = 0;
	 return;
  }
  nbroom = rand()%maxnb + minnb;
  for (int i = 0; i != nbroom; ++i) {
    rooms.push_back(Room(minW, maxW, minH, maxH));
  }
}

void RoomGenerator::AddRoomList(int x, int y, int w, int h)
{
  RoomList newroom;
  newroom.x = x;
  newroom.y = y;
  newroom.w = w;
  newroom.h = h;

  roomlist.push_back(newroom);
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

void RoomGenerator::ChooseDoor(std::list<Node> DoorNode, Cell **map, int dir)
{
  if (DoorNode.size() == 0)
    return;

  int n = rand()% DoorNode.size();
  std::list<Node>::iterator it = DoorNode.begin();
  std::advance(it, n);
  switch (dir) {
    case NORTH:
      map[it->x][it->y].GetCell()->DelWall(NORTH);
      map[it->x][it->y].GetCell()->SetDoor(NORTH);
      map[it->x][it->y - 1].GetCell()->DelWall(SOUTH);
      map[it->x][it->y - 1].GetCell()->SetDoor(SOUTH);
      return;
    case SOUTH:
      map[it->x][it->y].GetCell()->DelWall(SOUTH);
      map[it->x][it->y].GetCell()->SetDoor(SOUTH);
      map[it->x][it->y + 1].GetCell()->DelWall(NORTH);
      map[it->x][it->y + 1].GetCell()->SetDoor(NORTH);
      return;
    case WEST:
      map[it->x][it->y].GetCell()->DelWall(WEST);
      map[it->x][it->y].GetCell()->SetDoor(WEST);
      map[it->x - 1][it->y].GetCell()->DelWall(EAST);
      map[it->x - 1][it->y].GetCell()->SetDoor(EAST);
      return;
    case EAST:
      map[it->x][it->y].GetCell()->DelWall(EAST);
      map[it->x][it->y].GetCell()->SetDoor(EAST);
      map[it->x + 1][it->y].GetCell()->DelWall(WEST);
      map[it->x + 1][it->y].GetCell()->SetDoor(WEST);
      return;
  }
}

void RoomGenerator::PlaceDoors(Cell **map, int maxx, int maxy)
{
  while (!roomlist.empty()) {
    RoomList roomcur = roomlist.back(); 
    int j = roomcur.y;
    if (j != 0) {
      std::list<Node> DoorNode;
      for (int i = roomcur.x; i < roomcur.x+roomcur.w; ++i) {
        if (map[i][j - 1].GetCell()->GetType() == DIRT) {
          Node tmpnode;
          tmpnode.x = i;
          tmpnode.y = j;
          DoorNode.push_front(tmpnode);
        }
      }
      ChooseDoor(DoorNode, map, NORTH);
      DoorNode.clear();
    }
    j = roomcur.y + roomcur.h - 1;
    if (j != maxy) {
      std::list<Node> DoorNode;
      for (int i = roomcur.x; i < roomcur.x+roomcur.w; ++i) {
        if (map[i][j + 1].GetCell()->GetType() == DIRT) {
          Node tmpnode;
          tmpnode.x = i;
          tmpnode.y = j;
          DoorNode.push_front(tmpnode);
        } 
      }
      ChooseDoor(DoorNode, map, SOUTH);
      DoorNode.clear();
    }
    int i = roomcur.x;
    if (i != 0) {
      std::list<Node> DoorNode;
      for (int j = roomcur.y; j < roomcur.y + roomcur.h; ++j) {
        if (map[i-1][j].GetCell()->GetType() == DIRT) {
          Node tmpnode;
          tmpnode.x = i;
          tmpnode.y = j;
          DoorNode.push_front(tmpnode);
        }
      }
      ChooseDoor(DoorNode, map, WEST);
      DoorNode.clear();
    }
    i = roomcur.x + roomcur.w - 1;
    if (i != maxx) {
      std::list<Node> DoorNode;
      for (int j = roomcur.y; j < roomcur.y + roomcur.h; ++j) {
        if (map[i+1][j].GetCell()->GetType() == DIRT) {
          Node tmpnode;
          tmpnode.x = i;
          tmpnode.y = j;
          DoorNode.push_front(tmpnode);
        }
      }
      ChooseDoor(DoorNode, map, EAST);
      DoorNode.clear();
    }
    roomlist.pop_back();
  }
  roomlist.clear();
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
      AddRoomList(it->x, it->y, roomW, roomH);
      listrooms.clear();
      rooms.erase(rooms.begin());
    }
  }
  rooms.clear();
  PlaceDoors(maze.GetMaze(), maxx, maxy);
}
