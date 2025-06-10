#ifndef GAME_H
#define GAME_H

#include "food.h"
#include "map.h"
#include "snake.h"

typedef struct {
  SnakeMap    map;
  SnakeEntity snake;
  FoodEntity  food;
  int         update_per_second;
} SnakeGame;

typedef enum {
  PAUSE = 1,
  RUNNING,
  OVER,
  QUIT,
} GameState;

void Game_HandleKeyboardEvent(SnakeGame *this, KeyboardKey key);

bool Game_ColisionCheck(SnakeGame this);

void Game_IncreaseUpdateCycle(SnakeGame *this);

bool Game_IsFoodPositionValid(SnakeGame this);

void Game_Draw(SnakeGame game);

#endif
