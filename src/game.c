#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "object.h"
#include "game.h"

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

void Room_describe(void* self)
{
  assert(self);

  Room* room = self;

  if (room->proto.description)
    printf("%s\n", room->proto.description);

  if (room->bad_guy)
    printf("You see %s", room->bad_guy->_(description));
}


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


int run(Map* game)
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
