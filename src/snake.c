#include "snake.h"
#include "array-list/d_array_list.h"
#include <raylib.h>
#include <stdio.h>
// #include "map.h"

SnakeEntity NewSnakeEntity() {
  SnakeEntity snake = {
    .nodes               = NewArrayList(SnakeNode),
    .direction           = RIGHT,
    .color               = YELLOW,
    .impl_prev_direction = RIGHT,
  };

  SnakeNode first_node = {
    .x = 0,
    .y = 0,
  };

  PushItem(&snake.nodes, first_node);

  return snake;
}

void IncreaseSize(SnakeEntity *this) {
  size_t    head_index = this->nodes.length - 1;
  SnakeNode head       = GetAt(SnakeNode, this->nodes, head_index);

  switch (this->direction) {
    case RIGHT: head.x++;
    case LEFT: head.x--;
    case UP: head.y++;
    case DOWN: head.y--;
  }

  PushItem(&this->nodes, head);
}

void UpdateDirection(SnakeEntity *this, Direction dir) {
  if (                                           //
    this->direction == dir ||                    //
    (this->direction == LEFT && dir == RIGHT) || //
    (this->direction == RIGHT && dir == LEFT) || //
    (this->direction == UP && dir == DOWN) ||    //
    (this->direction == DOWN && dir == UP)       //
    )                                            //
    return;
  this->direction = dir;
}

void UpdateNodesPosition(SnakeEntity *this, Vector2D map_size) {
  SnakeNode *snake_nodes = GetArray(SnakeNode, &this->nodes);

  for (size_t i = 0; i < this->nodes.length; i++) {
    if (i == this->nodes.length - 1) {
      switch (this->direction) {
        case RIGHT:
          snake_nodes[i].x++; //
          break;
        case LEFT:
          snake_nodes[i].x--; //
          break;
        case UP:
          snake_nodes[i].y++; //
          break;
        case DOWN:
          snake_nodes[i].y--; //
          break;
      }

      if (snake_nodes[i].x < 0) {
        snake_nodes[i].x = map_size.x - 1;
      } else if (snake_nodes[i].x > (map_size.x - 1)) {
        snake_nodes[i].x = 0;
      } else if (snake_nodes[i].y < 0) {
        snake_nodes[i].y = map_size.y - 1;
      } else if (snake_nodes[i].y > (map_size.y - 1)) {
        snake_nodes[i].y = 0;
      }
      continue;
    }

    snake_nodes[i] = snake_nodes[i + 1];
  }

  this->impl_prev_direction = this->direction;
}