#ifndef FOOD_H
#define FOOD_H

#include "map.h"
#include <raylib.h>

typedef struct {
  Vector2D position;
  Color    color;
} FoodEntity;

void GenerateNewPosition(FoodEntity *this, Vector2D map_size);

FoodEntity NewFoodEntity(Vector2D map_size);

#endif