#include "game.h"
#include "map.h"
#include "raylib.h"
#include "snake.h"
#include <stddef.h>

int main(void) {
  auto game_size     = 650;
  auto window_width  = game_size;
  auto window_height = game_size;

  InitWindow(
    window_width, window_height, "raylib [core] example - basic window");

  auto map   = InitDefaultSquareMap(game_size, 25);
  auto snake = NewSnakeEntity();

  SnakeGame game = {
    .map   = map,
    .snake = snake,
  };

  int state = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyPressed(KEY_A)) {
      state = 1;
    }

    DrawGame(game);

    if (!state)
      DrawText("NO INPUT", 10, 10, 19, WHITE);
    else
      DrawText("INPUT PRESSED", 10, 10, 19, WHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}