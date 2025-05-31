#include "array-list/d_array_list.h"
#include "food.h"
#include "game.h"
#include "map.h"
#include "raylib.h"
#include "snake.h"
#include <stddef.h>
#include <stdio.h>

typedef enum {
  PAUSE = 1,
  RUNNING,
} GameState;

int main(void) {
  auto     game_size     = 650;
  auto     window_width  = game_size;
  auto     window_height = game_size;
  int      tile_count    = 15;
  Vector2D max_position  = {tile_count, tile_count};

  InitWindow(
    window_width, window_height, "raylib [core] example - basic window");

  auto map   = InitDefaultSquareMap(game_size, tile_count);
  auto snake = NewSnakeEntity();
  auto food  = NewFoodEntity(max_position);

  SnakeGame game = {
    .map               = map,
    .snake             = snake,
    .food              = food,
    .update_per_second = 3,
  };

  auto snake_nodes = GetArray(SnakeNode, &game.snake.nodes);
  snake_nodes[0].x = (int)(tile_count / 2);
  snake_nodes[0].y = (int)(tile_count / 2);

  IncreaseSize(&game.snake);
  UpdateNodesPosition(&game.snake, max_position);
  IncreaseSize(&game.snake);
  UpdateNodesPosition(&game.snake, max_position);

  SetTargetFPS(60);
  int       frames = 0;
  GameState state  = RUNNING;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE) && state == RUNNING) {
      state = PAUSE;
    } else if (IsKeyPressed(KEY_SPACE) && state == PAUSE) {
      state = RUNNING;
    }

    if (state != PAUSE) {

      frames = ((frames + 1) % 61);

      if (frames % (int)(60 / game.update_per_second) == 0) {
        UpdateNodesPosition(&game.snake, max_position);
      }

      KeyboardKey key = GetKeyPressed();
      if (key != KEY_NULL) KeyboardEventHandler(&game, key);

      if (ColisionCheck(game)) {
        IncreaseSize(&game.snake);

        GenerateNewPosition(&game.food, max_position);

        // TODO: Improve performance - everytime this check has to be performed
        // the game get stuck for some miliseconds
        while (!IsFoodPositionValid(game)) {
          printf("current food position: %d %d",
                 game.food.position.x,
                 game.food.position.x);
          GenerateNewPosition(&game.food, max_position);
        }

        IncreaseUpdateCycle(&game);
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    DrawGame(game);

    if (state == PAUSE) {
      const char *pause_text = "Game is Paused!";
      auto text_dim = MeasureTextEx(GetFontDefault(), pause_text, 25, 2.1);
      DrawRectangle(((float)game_size / 2) - (text_dim.x / 2) - 10,
                    ((float)game_size / 2) - (text_dim.y / 2) - 10,
                    text_dim.x + 20,
                    text_dim.y + 20,
                    BLACK);
      DrawText(pause_text,
               ((float)game_size / 2) - (text_dim.x / 2),
               ((float)game_size / 2) - (text_dim.y / 2),
               25,
               WHITE);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}