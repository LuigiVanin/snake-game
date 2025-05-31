#ifndef GAME_H
#define GAME_H
#include "game.h"
#include "array-list/d_array_list.h"
#include "map.h"
#include "snake.h"
#include <raylib.h>
#include <stddef.h>

void DrawGame(SnakeGame this) {
  auto map         = this.map;
  auto snake_nodes = GetArray(SnakeNode, &this.snake.nodes);

  for (size_t i = 0; i < map.tile_count.y; i++) {
    for (size_t j = 0; j < map.tile_count.x; j++) {
      DrawRectangle(                                          //
        (j * map.tile.width) + (double)map.tile.padding / 2,  //
        (i * map.tile.height) + (double)map.tile.padding / 2, //
        map.tile.width - (map.tile.padding),                  //
        map.tile.height - (map.tile.padding),                 //
        DARKGRAY                                              //
      );
    }
  }

  for (size_t i = 0; i < this.snake.nodes.length; i++) {
    auto curr_node    = snake_nodes[i];
    auto curr_padding = i == this.snake.nodes.length - 1          //
                          ? map.tile.padding                      //
                          : map.tile.padding + 2;                 //
    DrawRectangle(                                                //
      (curr_node.x * map.tile.width) + (double)curr_padding / 2,  //
      (curr_node.y * map.tile.height) + (double)curr_padding / 2, //
      map.tile.width - (curr_padding),                            //
      map.tile.height - (curr_padding),                           //
      this.snake.color                                            //
    );
  }

  DrawRectangle(                                                             //
    (this.food.position.x * map.tile.width) + (double)map.tile.padding / 2,  //
    (this.food.position.y * map.tile.height) + (double)map.tile.padding / 2, //
    map.tile.width - (map.tile.padding),                                     //
    map.tile.height - (map.tile.padding),                                    //
    this.food.color                                                          //
  );
}

void KeyboardEventHandler(SnakeGame *this, KeyboardKey key) {
  if (key == KEY_A || key == KEY_LEFT)
    UpdateDirection(&this->snake, LEFT);
  else if (key == KEY_D || key == KEY_RIGHT)
    UpdateDirection(&this->snake, RIGHT);
  else if (key == KEY_S || key == KEY_DOWN)
    UpdateDirection(&this->snake, UP);
  else if (key == KEY_W || key == KEY_UP)
    UpdateDirection(&this->snake, DOWN);
}

bool ColisionCheck(SnakeGame this) {
  size_t    head_index = this.snake.nodes.length - 1;
  SnakeNode head       = GetAt(SnakeNode, this.snake.nodes, head_index);

  if (head.x == this.food.position.x && head.y == this.food.position.y) {
    return true;
  }

  return false;
}

void IncreaseUpdateCycle(SnakeGame *this) {
  if (this->update_per_second == 12) return;
  this->update_per_second++;
}

bool IsFoodPositionValid(SnakeGame this) {
  auto snake_nodes = GetArray(SnakeNode, &this.snake.nodes);

  for (size_t i = 0; i < this.snake.nodes.length; i++) {
    if (snake_nodes[i].x == this.food.position.x &&
        snake_nodes[i].y == this.food.position.y)
      return false;
  }

  return true;
}
#endif