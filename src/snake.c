#include "snake.h"
#include "array-list/d_array_list.h"
// #include "map.h"

SnakeEntity NewSnakeEntity() {
  SnakeEntity snake = {
    .nodes     = NewArrayList(SnakeNode),
    .direction = RIGHT,
    .color     = YELLOW,
  };

  return snake;
}

void Increase(SnakeEntity *this) {
  size_t    head_index = this->nodes.length;
  SnakeNode head       = GetAt(SnakeNode, this->nodes, head_index);

  switch (this->direction) {
    case RIGHT: head.x++;
    case LEFT: head.x--;
    case UP: head.y++;
    case DOWN: head.y--;
  }

  PushItem(&this->nodes, head);
}

void UpdateNodesPosition(SnakeEntity *this) {
  // SnakeNode *snake_nodes = (SnakeNode *)this->nodes.data;
  SnakeNode *snake_nodes = GetArray(SnakeNode, &this->nodes);

  for (size_t i = 0; i < this->nodes.length; i++) {

    if (i == this->nodes.length - 1) {

      switch (this->direction) {
        case RIGHT: snake_nodes[i].x++;
        case LEFT: snake_nodes[i].x--;
        case UP: snake_nodes[i].y++;
        case DOWN: snake_nodes[i].y--;
      }
      continue;
    }

    snake_nodes[i] = snake_nodes[i + 1];
  }
}