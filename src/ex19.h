#ifndef _ex19_h
#define _ex19_h

#include "object.h"

struct Monster {
  Object proto;
  int hit_points;
};

typedef struct Monster Monster;

int Monster_attack(void* self, int damage);


struct Room {
  Object proto;

  Monster* bad_guy;

  struct Room* north;
  struct Room* south;
  struct Room* east;
  struct Room* west;
};

typedef struct Room Room;

void* Room_move(void* self, Direction direction);
int Room_attack(void* self, int damage);
void Room_describe(void* self);

struct Map {
  Object proto;

  Room* start;
  Room* location;
};

typedef struct Map Map;

void* Map_move(void* self, Direction direction);
int Map_attack(void* self, int damage);
int Map_init(void* self);

#endif
