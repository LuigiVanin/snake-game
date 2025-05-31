#ifndef GAME_H
#define GAME_H
#include "game.h"
#include "map.h"
#include <math.h>
#include <stddef.h>

void DrawGame(SnakeGame game) {
  auto map = game.map;

  for (size_t i = 0; i < map.tile_count.y; i++) {
    for (size_t j = 0; j < map.tile_count.x; j++) {
      DrawRectangle(                                                //
        (j * map.tile.width) + ceil((double)map.tile.padding / 2),  //
        (i * map.tile.height) + ceil((double)map.tile.padding / 2), //
        map.tile.width - (map.tile.padding),                        //
        map.tile.height - (map.tile.padding),                       //
        DARKGRAY                                                    //
      );
    }
  }
}

#endif