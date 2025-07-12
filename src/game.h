#ifndef GAME_H
#define GAME_H

#include "food.h"
#include "map.h"
#include "snake.h"

typedef enum {
  PAUSE = 1,
  RUNNING,
  OVER,
  QUIT,
} GameState;

typedef struct {
  SnakeMap    map;
  SnakeEntity snake;
  FoodEntity  food;
  GameState   state;
  int         update_per_second;
  int         tick;
} SnakeGame;

SnakeGame NewGame(SnakeMap map, SnakeEntity snake, FoodEntity food);

void Game_HandleKeyboardEvent(SnakeGame *this, KeyboardKey key);

bool Game_ColisionCheck(SnakeGame this);

void Game_IncreaseUpdateCycle(SnakeGame *this);

bool Game_IsFoodPositionValid(SnakeGame this);

void Game_Draw(SnakeGame game);

void Game_Cycle(SnakeGame *game, KeyboardKey key, Vector2D max_position);

void Game_Reset(SnakeGame *game);
#endif
