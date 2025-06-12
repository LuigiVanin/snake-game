#include "food.h"
#include "game.h"
#include "gui/pause.h"
#include "map.h"
#include "raylib.h"
#include "snake.h"
#include <stddef.h>

int main(void) {
  auto     game_size     = 650;
  auto     window_width  = game_size;
  auto     window_height = game_size;
  auto     tile_count    = 15;
  Vector2D max_position  = {tile_count, tile_count};

  InitWindow(
    window_width, window_height, "raylib [core] example - basic window");

  auto map   = InitDefaultSquareMap(game_size, tile_count);
  auto snake = InitDefaultSnake(map, 3);
  auto food  = NewFoodEntity(max_position);
  auto pause = NewPauseGui("Game is Paused!", NewVector2D(300, 450));
  auto game  = NewGame(map, snake, food);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    KeyboardKey key = GetKeyPressed();
    Pause_HandleEvent(pause, &game, key);

    if (game.state == RUNNING) {
      Game_Cycle(&game, key, max_position);

    } else if (game.state == PAUSE) {
      game.state = Pause_Cycle(&pause);
    }

    BeginDrawing();
    ClearBackground(BLACK);

    Game_Draw(game);

    // DRAW GUI
    if (game.state == PAUSE) {
      Pause_Draw(pause, game_size);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}