#include <cstdlib>
#include <iostream>
#include "room.h"

Room::Room(int minW, int maxW, int minH, int maxH)
{
  roomW = rand()%(maxW - minW) + minW;
  roomH = rand()%(maxH - minH) + minH;
}