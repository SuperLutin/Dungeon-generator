#include <cstdlib>
#include <iostream>
#include "room.h"

Room::Room(int minW, int maxW, int minH, int maxH)
{
  if (minW == maxW)
  {
    roomW = minW;
    roomH = minW;
  }
  else
  {
    roomW = rand()%(maxW - minW) + minW;
    roomH = rand()%(maxH - minH) + minH;
  }
}

Room::Room(int w, int h)
{
  roomW = w;
  roomH = h;
}
