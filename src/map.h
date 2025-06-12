#ifndef MAP_H
#define MAP_H
#include "raylib.h"
#include <stddef.h>

typedef struct {
  int x;
  int y;
} Vector2D;

Vector2D NewVector2D(int x, int y);

typedef struct Vector2D Position;

typedef struct {
  int    count;
  double padding;
  double width;
  double height;
  Color  color;

} TileOption;

typedef struct {
  int        width;
  int        height;
  Vector2D   tile_count;
  TileOption tile;
} SnakeMap;

TileOption NewTileOption(int    tile_count,
                         double tile_width,
                         double tile_height,
                         double tile_padding,
                         Color  tile_color);

SnakeMap NewSnakeMap(int        width,
                     int        height,
                     Vector2D   tile_count,
                     TileOption tile_options);

SnakeMap InitDefaultSquareMap(int size, int tile_count);

void Map_Draw(SnakeMap this);

#endif