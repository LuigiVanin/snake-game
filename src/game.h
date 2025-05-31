#include "map.h"
#include "snake.h"

typedef struct {
  SnakeMap    map;
  SnakeEntity snake;
} SnakeGame;

void DrawGame(SnakeGame game);
