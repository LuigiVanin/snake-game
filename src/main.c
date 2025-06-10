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
    KeyboardKey key = GetKeyPressed();

    state = Pause_HandleEvent(pause, key, state);

    if (state == RUNNING) {
      // TODO: Improve frame counting implementation
      frames = ((frames + 1) % 61);

      if (frames % (int)(60 / game.update_per_second) == 0) {
        Snake_Move(&game.snake, max_position);
      }

      if (key != KEY_NULL) Game_HandleKeyboardEvent(&game, key);

      if (Snake_CheckSelfCollision(game.snake)) {
        state = PAUSE;
      }

      if (Game_ColisionCheck(game)) {
        Snake_IncreaseSize(&game.snake);

        Food_GenerateNewPosition(&game.food, max_position);

        while (!Game_IsFoodPositionValid(game)) {
          Food_GenerateNewPosition(&game.food, max_position);
        }

        Game_IncreaseUpdateCycle(&game);
      }
    } else if (state == PAUSE) {
      state = Pause_Cycle(&pause);
    }

    BeginDrawing();
    ClearBackground(BLACK);

    Game_Draw(game);

    // DRAW GUI
    if (state == PAUSE) {
      Pause_Draw(pause, game_size);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}