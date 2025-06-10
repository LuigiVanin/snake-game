#include "game.h"
#include "array-list/d_array_list.h"
#include "food.h"
#include "map.h"
#include "snake.h"
#include <raylib.h>
#include <stddef.h>

void Game_Draw(SnakeGame this) {
  Map_Draw(this.map);
  Snake_Draw(this.snake, this.map);
  Food_Draw(this.food, this.map);
}

void Game_HandleKeyboardEvent(SnakeGame *this, KeyboardKey key) {
  if (key == KEY_A || key == KEY_LEFT)
    Snake_UpdateDirection(&this->snake, LEFT);
  else if (key == KEY_D || key == KEY_RIGHT)
    Snake_UpdateDirection(&this->snake, RIGHT);
  else if (key == KEY_S || key == KEY_DOWN)
    Snake_UpdateDirection(&this->snake, UP);
  else if (key == KEY_W || key == KEY_UP)
    Snake_UpdateDirection(&this->snake, DOWN);
}

bool Game_ColisionCheck(SnakeGame this) {
  size_t    head_index = this.snake.nodes.length - 1;
  SnakeNode head       = GetAt(SnakeNode, this.snake.nodes, head_index);

  if (head.x == this.food.position.x && head.y == this.food.position.y) {
    return true;
  }

  return false;
}

void Game_IncreaseUpdateCycle(SnakeGame *this) {
  if (this->update_per_second == 12) return;
  this->update_per_second++;
}

bool Game_IsFoodPositionValid(SnakeGame this) {
  auto snake_nodes = GetArray(SnakeNode, &this.snake.nodes);

  for (size_t i = 0; i < this.snake.nodes.length; i++) {
    if (snake_nodes[i].x == this.food.position.x &&
        snake_nodes[i].y == this.food.position.y)
      return false;
  }

  return true;
}
