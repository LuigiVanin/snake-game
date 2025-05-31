#include "map.h"

TileOption NewTileOption(int    tile_count,
                         double tile_width,
                         double tile_height,
                         double tile_padding,
                         Color  tile_color) {
  TileOption options = {
    .padding = tile_padding,
    .width   = tile_width,
    .height  = tile_height,
    .color   = tile_color,
    .count   = tile_count,
  };
  return options;
}

SnakeMap NewSnakeMap(int        width,
                     int        height,
                     Vector2D   tile_count,
                     TileOption tile_options) {
  SnakeMap map = {
    .width      = width,
    .height     = height,
    .tile       = tile_options,
    .tile_count = tile_count,
  };
  return map;
}

SnakeMap InitDefaultSquareMap(int size, int tile_count) {
  TileOption tile_options = {
    .padding = 3,
    .height  = (double)size / tile_count,
    .width   = (double)size / tile_count,
    .color   = DARKGRAY,
  };

  Vector2D count = {
    .x = tile_count,
    .y = tile_count,
  };

  return NewSnakeMap(size, size, count, tile_options);
}