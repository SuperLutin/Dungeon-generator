#include "cell.h"
#include "maze.h"

int Cell::CountWall(){
  return (wallN + wallS + wallE + wallW);
}

bool Cell::isWall(int dir)
{
  if (dir == NORTH)
    return wallN;
  if (dir == SOUTH)
    return wallS;
  if (dir == EAST)
    return wallE;
  if (dir == WEST)
    return wallW;

  return false;
}

bool Cell::isDoor(int dir)
{
  if (dir == NORTH)
    return doorN;
  if (dir == SOUTH)
    return doorS;
  if (dir == EAST)
    return doorE;
  if (dir == WEST)
    return doorW;

  return false;
}



void Cell::SetWall(int wall)
{
  if (wall == NORTH) {
    wallN = true;
    return;
  }
  if (wall == SOUTH) {
    wallS = true;
    return;
  }
  if (wall == EAST) {
    wallE = true;
    return;
  }
  if (wall == WEST) {
    wallW = true;
    return;
  }
}

void Cell::SetDoor(int door)
{
  if (door == NORTH) {
    doorN = true;
    return;
  }
  if (door == SOUTH) {
    doorS = true;
    return;
  }
  if (door == EAST) {
    doorE = true;
    return;
  }
  if (door == WEST) {
    doorW = true;
    return;
  }
}

void Cell::DelWall(int wall)
{
  if (wall == NORTH) {
    wallN = false;
    return;
  }
  if (wall == SOUTH) {
    wallS = false;
    return;
  }
  if (wall == EAST) {
    wallE = false;
    return;
  }
  if (wall == WEST) {
    wallW = false;
    return;
  }
}
