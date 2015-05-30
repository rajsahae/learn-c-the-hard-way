#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "ex19.h"

int Monster_attack(void* self, int damage)
{
  assert(self);
  assert(damage >= 0);

  Monster *monster = self;
  assert(monster->hit_points > 0);

  if (damage == 0) {
    printf("WHOOSH! Your attack missed!\n");
  } else {
    printf("You attack %s for %d damage!\n", monster->_(description), damage);
    monster->hit_points -= damage;
  }

  if (monster->hit_points > 0) {
    printf("%s still has %d hitpoints!\n", monster->_(description), monster->hit_points);
    return 0;
  } else {
    printf("It is dead!\n");
    return 1;
  }
}

Object MonsterProto = {
  .attack = Monster_attack
};


void* Room_move(void* self, Direction direction)
{
  assert(self);

  Room* room = self;
  Room* next = NULL;

  if (direction == NORTH && room->north) {
    printf("You go north, into:\n");
    next = room->north;
  } else if (direction == SOUTH && room->south) {
    printf("You go south, into:\n");
    next = room->south;
  } else if (direction == EAST && room->east) {
    printf("You go east, into:\n");
    next = room->east;
  }  else if (direction == WEST && room->west) {
    printf("You go west, into:\n");
    next = room->west;
  } else {
    printf("You can't go that direction");
    next = NULL;
  }

  if (next)
    next->_(describe)(next);

  return next;
}

int Room_attack(void* self, int damage)
{
  assert(self);
  assert(damage >= 0);

  Room* room = self;
  Monster* monster = room->bad_guy;

  if (monster) {
    if (monster->_(attack)(monster, damage)) {
      free(room->bad_guy);
      room->bad_guy = NULL;
    }
    return 1;
  } else {
    printf("You flail in the air at nothing...Idiot\n");
    return 0;
  }
}

Object RoomProto = {
  .move = Room_move,
  .attack = Room_attack
};


void* Map_move(void* self, Direction direction)
{
  assert(self);

  Map* map = self;
  Room* location = map->location;
  Room* next = NULL;

  assert(location);

  next = location->_(move)(location, direction);

  if (next)
    map->location = next;

  return next;
}

int Map_attack(void* self, int damage)
{
  assert(self);
  assert(damage >= 0);

  Map* map = self;
  Room* location = map->location;

  assert(location);

  return location->_(attack)(location, damage);
}

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

Object MapProto = {
  .init = Map_init,
  .move = Map_move,
  .attack = Map_attack
};

int process_input(Map* game)
{
  assert(game);

  printf("\n> ");

  char ch = getchar();
  getchar(); // eat ENTER

  int damage = rand() % 4;

  switch(ch) {
    case EOF:
      printf("Giving up? You suck\n");
      return 0;

    case 'n':
      game->_(move)(game, NORTH);
      break;

    case 's':
      game->_(move)(game, SOUTH);
      break;

    case 'e':
      game->_(move)(game, EAST);
      break;

    case 'w':
      game->_(move)(game, WEST);
      break;

    case 'a':
      game->_(attack)(game, damage);
      break;

    case 'l':
      printf("You can go:\n");
      if (game->location->north) printf("North\n");
      if (game->location->south) printf("South\n");
      if (game->location->east ) printf("East\n" );
      if (game->location->west ) printf("West\n" );
      break;

    default:
      printf("What?: %c\n", ch);
  }

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

  while(process_input(game)) {}

  return 0;
}
