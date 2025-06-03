#ifndef FOOD_H
#define FOOD_H

#include "map.h"
#include <raylib.h>

typedef struct {
  Vector2D position;
  Color    color;
} FoodEntity;

FoodEntity NewFoodEntity(Vector2D map_size);

void Food_GenerateNewPosition(FoodEntity *this, Vector2D map_size);

void Food_Draw(FoodEntity this, SnakeMap map);

#endif