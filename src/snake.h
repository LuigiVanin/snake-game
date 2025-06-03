#ifndef SNAKE_H
#define SNAKE_H

#include "array-list/d_array_list.h"
#include "map.h"
#include <raylib.h>

typedef struct {
  int x;
  int y;
} SnakeNode;

typedef enum { RIGHT = 0, LEFT, UP, DOWN } Direction;

typedef struct {
  ArrayList nodes;
  Direction direction;
  Direction impl_prev_direction;
  Color     color;

} SnakeEntity;

SnakeEntity NewSnakeEntity();

SnakeEntity InitDefaultSnake(SnakeMap map, int snake_initial_size);

void Snake_UpdateNodesPosition(SnakeEntity *this, Vector2D map_size);

void Snake_UpdateDirection(SnakeEntity *this, Direction dir);

void Snake_IncreaseSize(SnakeEntity *this);

void Snake_Draw(SnakeEntity this, SnakeMap map);

#endif