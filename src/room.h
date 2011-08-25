#ifndef ROOM_H
#define ROOM_H

class Room
{
  int roomW;
  int roomH;
public :
  Room(int minW, int maxW, int minH, int maxH);
  int GetRoomW() { return roomW; }
  int GetRoomH() { return roomH; }
};

#endif
