#ifndef SNAKE_H
#define SNAKE_H

#include "array-list/d_array_list.h"
#include <raylib.h>

typedef struct {
  int x;
  int y;
} SnakeNode;

typedef enum { RIGHT = 0, LEFT, UP, DOWN } Direction;

typedef struct {
  ArrayList nodes;
  Direction direction;
  Color     color;
} SnakeEntity;

SnakeEntity NewSnakeEntity();

void UpdateNodesPosition(SnakeEntity *this);

#endif