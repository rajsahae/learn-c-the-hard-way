#ifndef _game_h
#define _game_h

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

int run(Map* game);

static Object MonsterProto = {
  .attack = Monster_attack
};

static Object RoomProto = {
  .move = Room_move,
  .attack = Room_attack,
  .describe = Room_describe
};

static Object MapProto = {
  .init = Map_init,
  .move = Map_move,
  .attack = Map_attack
};


#endif
