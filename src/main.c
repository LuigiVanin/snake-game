#include "food.h"
#include "game.h"
#include "gui/pause.h"
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
  auto snake = InitDefaultSnake(map, 3);
  auto food  = NewFoodEntity(max_position);
  auto pause = NewPauseGui("Game is Paused!");

  SnakeGame game = {
    .map               = map,
    .snake             = snake,
    .food              = food,
    .update_per_second = 3,
  };

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
        Snake_UpdateNodesPosition(&game.snake, max_position);
      }

      KeyboardKey key = GetKeyPressed();
      if (key != KEY_NULL) Game_KeyboardEventHandler(&game, key);

      if (Game_ColisionCheck(game)) {
        Snake_IncreaseSize(&game.snake);

        Food_GenerateNewPosition(&game.food, max_position);

        // TODO: Improve performance - everytime this check has to be performed
        // the game get stuck for some miliseconds
        while (!Game_IsFoodPositionValid(game)) {
          printf("current food position: %d %d",
                 game.food.position.x,
                 game.food.position.x);
          Food_GenerateNewPosition(&game.food, max_position);
        }

        Game_IncreaseUpdateCycle(&game);
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    Game_Draw(game);

    if (state == PAUSE) {
      Pause_Draw(pause, game_size);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}