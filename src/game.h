#include "food.h"
#include "map.h"
#include "snake.h"

typedef struct {
  SnakeMap    map;
  SnakeEntity snake;
  FoodEntity  food;
  int         update_per_second;
} SnakeGame;

void Game_KeyboardEventHandler(SnakeGame *this, KeyboardKey key);

bool Game_ColisionCheck(SnakeGame this);

void Game_IncreaseUpdateCycle(SnakeGame *this);

bool Game_IsFoodPositionValid(SnakeGame this);

void Game_Draw(SnakeGame game);
