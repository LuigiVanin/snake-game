#include "snake.h"
#include "array-list/d_array_list.h"
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
// #include "map.h"

SnakeEntity NewSnakeEntity() {
  SnakeEntity snake = {
    .nodes          = NewArrayList(SnakeNode),
    .direction      = RIGHT,
    .color          = YELLOW,
    .prev_direction = RIGHT,
  };

  SnakeNode first_node = {
    .x = 0,
    .y = 0,
  };

  PushItem(&snake.nodes, first_node);

  return snake;
}

SnakeEntity InitDefaultSnake(SnakeMap map, int snake_initial_size) {
  auto this = NewSnakeEntity();

  auto snake_nodes = GetArray(SnakeNode, &this.nodes);
  snake_nodes[0].x = (int)(map.tile_count.x / 2);
  snake_nodes[0].y = (int)(map.tile_count.y / 2);

  for (size_t i = 0; i < (size_t)(snake_initial_size - 1); i++) {
    Snake_IncreaseSize(&this);
    Snake_Move(&this, map.tile_count);
  }

  return this;
}

void Snake_IncreaseSize(SnakeEntity *this) {
  size_t    head_index = this->nodes.length - 1;
  SnakeNode head       = GetAt(SnakeNode, this->nodes, head_index);

  if (this->direction == RIGHT)
    head.x++;
  else if (this->direction == LEFT)
    head.x--;
  else if (this->direction == UP)
    head.y++;
  else if (this->direction == DOWN)
    head.y--;

  PushItem(&this->nodes, head);
}

void Snake_UpdateDirection(SnakeEntity *this, Direction dir) {
  if (                                                //
    this->prev_direction == dir ||                    //
    (this->prev_direction == LEFT && dir == RIGHT) || //
    (this->prev_direction == RIGHT && dir == LEFT) || //
    (this->prev_direction == UP && dir == DOWN) ||    //
    (this->prev_direction == DOWN && dir == UP)       //
    )                                                 //
    return;
  this->direction = dir;
}

void Snake_Move(SnakeEntity *this, Vector2D map_size) {
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

  this->prev_direction = this->direction;
}

bool Snake_CheckSelfCollision(SnakeEntity this) {
  auto nodes = GetArray(SnakeNode, &this.nodes);

  for (size_t i = 0; i < this.nodes.length; i++) {
    for (size_t j = 0; j < this.nodes.length; j++) {
      if (i == j) continue;
      if (nodes[i].x == nodes[j].x && nodes[i].y == nodes[j].y) return true;
    }
  }

  return false;
}

void Snake_Draw(SnakeEntity this, SnakeMap map) {
  auto snake_nodes = GetArray(SnakeNode, &this.nodes);

  for (size_t i = 0; i < this.nodes.length; i++) {
    auto curr_node    = snake_nodes[i];
    auto curr_padding = i == this.nodes.length - 1                //
                          ? map.tile.padding                      //
                          : map.tile.padding + 2;                 //
    DrawRectangle(                                                //
      (curr_node.x * map.tile.width) + (double)curr_padding / 2,  //
      (curr_node.y * map.tile.height) + (double)curr_padding / 2, //
      map.tile.width - (curr_padding),                            //
      map.tile.height - (curr_padding),                           //
      this.color                                                  //
    );
  }
}
