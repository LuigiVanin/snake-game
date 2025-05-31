#include "food.h"
#include "map.h"
#include "snake.h"

typedef struct {
  SnakeMap    map;
  SnakeEntity snake;
  FoodEntity  food;
  int         update_per_second;
} SnakeGame;

void KeyboardEventHandler(SnakeGame *this, KeyboardKey key);

bool ColisionCheck(SnakeGame this);

void IncreaseUpdateCycle(SnakeGame *this);

bool IsFoodPositionValid(SnakeGame this);

void DrawGame(SnakeGame game);
