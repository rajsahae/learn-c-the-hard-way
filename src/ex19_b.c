#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "game.h"

int Map_init(void* self)
{
  assert(self);

  Map* map = self;

  // make some rooms for a small map
  Room* hallway       = NEW(Room, "entrance hallway");
  Room* livingRoom    = NEW(Room, "living room");
  Room* kitchen       = NEW(Room, "kitchen, you need a snack?");
  Room* halfBath      = NEW(Room, "downstairs bathroom");
  Room* laundry       = NEW(Room, "laundry room");
  Room* patio         = NEW(Room, "back patio");
  Room* stairs        = NEW(Room, "stairs to the second story");
  Room* guestRoom     = NEW(Room, "guest room");
  Room* guestBath     = NEW(Room, "guest bathroom");
  Room* nursery       = NEW(Room, "nursery");
  Room* masterBedroom = NEW(Room, "master bedroom");
  Room* masterBath    = NEW(Room, "master bathroom");
  Room* closet        = NEW(Room, "walk in closet");

  assert(hallway);
  assert(livingRoom);
  assert(kitchen);
  assert(halfBath);
  assert(laundry);
  assert(patio);
  assert(guestRoom);
  assert(guestBath);
  assert(nursery);
  assert(masterBedroom);
  assert(masterBath);
  assert(closet);

  // No bad guys in this one. Just the map
  // Setup the rooms
  hallway->west = livingRoom;
  hallway->north = kitchen;
  hallway->south = laundry;
  hallway->east = halfBath;

  livingRoom->east = hallway;
  livingRoom->north = kitchen;
  livingRoom->west = patio;
  livingRoom->south = stairs;

  kitchen->south = hallway;
  kitchen->west = livingRoom;

  halfBath->north = hallway;
  laundry->north = hallway;
  patio->east = livingRoom;
  
  stairs->south = livingRoom;
  stairs->west = guestBath;
  stairs->north = guestRoom;
  stairs->east = nursery;

  guestBath->east = stairs;
  guestRoom->south = stairs;

  nursery->west = stairs;
  nursery->east = masterBedroom;

  masterBedroom->west = nursery;
  masterBedroom->east = masterBath;
  masterBedroom->north = closet;

  masterBath->west = masterBedroom;
  closet->south = masterBedroom;

  // start the map and the character off in the hallway
  map->start = hallway;
  map->location = hallway;

  return 1;
}

int main(int argc, char* argv[])
{
  // seed random number generator
  srand(time(NULL));

  // make the map
  Map *game = NEW(Map, "843 N Humboldt St");

  assert(game);
  assert(game->location);

  printf("You enter the ");
  game->location->_(describe)(game->location);

  while(run(game)) {}

  return 0;
}
