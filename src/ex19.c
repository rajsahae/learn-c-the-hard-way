#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "game.h"

Object MonsterProto = {
  .attack = Monster_attack
};

Object RoomProto = {
  .move = Room_move,
  .attack = Room_attack,
  .describe = Room_describe
};

Object MapProto = {
  .init = Map_init,
  .move = Map_move,
  .attack = Map_attack
};

int Map_init(void* self)
{
  assert(self);

  Map* map = self;

  // make some rooms for a small map
  Room* hall      = NEW(Room, "The great Hall");
  Room* throne    = NEW(Room, "The throne room");
  Room* arena     = NEW(Room, "The arena, with The Minotaur");
  Room* kitchen   = NEW(Room, "The Kitchen, you need a snack?");
  Room* quarters  = NEW(Room, "The servants quarters");
  Room* courtyard = NEW(Room, "The courtyard to the castle");
  Room* guest     = NEW(Room, "The guest quarters");

  assert(hall);
  assert(throne);
  assert(arena);
  assert(kitchen);
  assert(quarters);
  assert(courtyard);
  assert(guest);

  // Populate the bad guys
  arena->bad_guy     = NEW(Monster, "The evil minotaur");
  quarters->bad_guy  = NEW(Monster, "A disgruntled worker!");
  guest->bad_guy     = NEW(Monster, "A seriously neglected visitor!");
  courtyard->bad_guy = NEW(Monster, "A rabid squirell!");

  assert(arena->bad_guy);
  assert(quarters->bad_guy);
  assert(courtyard->bad_guy);
  assert(guest->bad_guy);

  arena->bad_guy->hit_points = 20;
  quarters->bad_guy->hit_points = 10;
  guest->bad_guy->hit_points = 10;
  courtyard->bad_guy->hit_points = 5;

  // Setup the map rooms
  throne->west  = arena;
  throne->east  = kitchen;
  throne->south = hall;

  arena->east   = throne;
  kitchen->west = throne;
  hall->north   = throne;

  hall->west = quarters;
  hall->east = guest;
  hall->south = courtyard;

  quarters->east = hall;
  guest->west = hall;
  courtyard->north = hall;

  // start the map and the character off in the hall
  map->start = courtyard;
  map->location = courtyard;

  return 1;
}

int main(int argc, char* argv[])
{
  // seed random number generator
  srand(time(NULL));

  // make the map
  Map *game = NEW(Map, "The Hall of the Minotaur");

  assert(game);
  assert(game->location);

  printf("You enter the ");
  game->location->_(describe)(game->location);

  while(run(game)) {}

  return 0;
}
