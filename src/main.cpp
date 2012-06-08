#include <iostream>
#include <cstdlib>

#include "config.h"
#include "maze.h"
#include "cell.h"
#include "roomgenerator.h"

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;

  Config config;
  unsigned int x;
  unsigned int y;
  unsigned int randomness;
  unsigned int sparseness;
  unsigned int loopness;
  unsigned int minroom;
  unsigned int maxroom;
  unsigned int minwidth;
  unsigned int maxwidth;
  unsigned int minheight;
  unsigned int maxheight;
  config.Load(".config");

  if (! (config.Get("x", x) &&
         config.Get("y", y) &&
         config.Get("randomness", randomness) &&
         config.Get("sparseness", sparseness) &&
         config.Get("loopness", loopness) &&
         config.Get("minroom", minroom) &&
         config.Get("maxroom", maxroom) &&
         config.Get("minwidth", minwidth) &&
         config.Get("maxwidth", maxwidth) &&
         config.Get("minheight", minheight) &&
         config.Get("maxheight", maxheight))) {
    std::cerr << "Missing parameter in configuration file." << std::endl;
    return -1;
  }

  if (randomness > 100) {
    std::cerr << "Randomness must be between 0 and 100." << std::endl;
    return -1;
  }
  if (sparseness > 100) {
    std::cerr << "Sparseness must be between 0 and 100." << std::endl;
    return -1;
  }
  if (loopness > 100) {
    std::cerr << "Loopness must be between 0 and 100." << std::endl;
    return -1;
  }
  if ( maxwidth > x || maxwidth < minwidth) {
    std::cerr << "There is a problem with room's width" << std::endl;
    return -1;
  }
  if ( maxheight > y || maxheight < minheight) {
    std::cerr << "There is a problem with room's height" << std::endl;
    return -1;
  }

  Maze *map = new Maze(x, y, randomness, sparseness, loopness);
  map->Dig();
  map->Fill();
  map->CreateLoop();

  RoomGenerator *rooms = new RoomGenerator(minroom, maxroom,
                                           minwidth, maxwidth,
                                           minheight, maxheight);

  rooms->SearchPlace(*map);

  map->WriteDungeon();

  delete rooms;
  delete map;
  return 0;
}
