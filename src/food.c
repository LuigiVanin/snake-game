#include "food.h"
#include "map.h"
#include <raylib.h>
#include <stdlib.h>
// #include <time.h>

void Food_GenerateNewPosition(FoodEntity *this, Vector2D map_size) {

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

  Food_GenerateNewPosition(&food, map_size);

  return food;
};

void Food_Draw(FoodEntity this, SnakeMap map) {
  DrawRectangle(                                                        //
    (this.position.x * map.tile.width) + (double)map.tile.padding / 2,  //
    (this.position.y * map.tile.height) + (double)map.tile.padding / 2, //
    map.tile.width - (map.tile.padding),                                //
    map.tile.height - (map.tile.padding),                               //
    this.color                                                          //
  );
}