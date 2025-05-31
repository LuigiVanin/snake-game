#include "food.h"
#include "map.h"
#include <raylib.h>
#include <stdlib.h>
// #include <time.h>

void GenerateNewPosition(FoodEntity *this, Vector2D map_size) {

  Vector2D position = {
    .x = rand() % map_size.x,
    .y = rand() % map_size.y,
  };
  this->position = position;
}

FoodEntity NewFoodEntity(Vector2D map_size) {

  FoodEntity food = {
    .color = RED,
  };

  GenerateNewPosition(&food, map_size);

  return food;
};