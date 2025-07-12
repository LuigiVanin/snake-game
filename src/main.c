#include "food.h"
#include "game.h"
#include "gui/menu.h"
#include "gui/pause.h"
#include "map.h"
#include "raylib.h"
#include "snake.h"
#include <stddef.h>

typedef enum {
  MENU,
  GAME,
} GameScene;

int main(void) {
  auto     game_size     = 650;
  auto     window_width  = game_size;
  auto     window_height = game_size;
  auto     tile_count    = 20;
  Vector2D max_position  = {tile_count, tile_count};

  GameScene current_game_scene = MENU;

  InitWindow(
    window_width, window_height, "raylib [core] example - basic window");

  auto       menu  = NewMenu("Snake Game!!");
  auto       map   = InitDefaultSquareMap(game_size, tile_count);
  auto       snake = InitDefaultSnake(map, 3);
  auto       food  = NewFoodEntity(max_position);
  auto       pause = NewPauseGui("Game is Paused!", NewVector2D(300, 200));
  auto       game  = NewGame(map, snake, food);
  MenuOption menu_select = NONE;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    KeyboardKey key = GetKeyPressed();

    if (current_game_scene == GAME) {
      Pause_HandleEvent(pause, &game, key);

      if (game.state == RUNNING) {
        Game_Cycle(&game, key, max_position);

      } else if (game.state == PAUSE) {
        game.state = Pause_Cycle(&pause, key);
      } else if (game.state == QUIT) {
        current_game_scene = MENU;
        game.state         = RUNNING;
        Game_Reset(&game);
      }
    } else if (current_game_scene == MENU) {
      menu_select = Menu_Cycle(&menu, key);
      if (menu_select == NEW) {
        Game_Reset(&game);
        current_game_scene = GAME;
      }
      if (menu_select == QUIT_GAME) {
        CloseWindow();
        return 0;
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);
    if (current_game_scene == GAME) {

      Game_Draw(game);

      // DRAW GUI
      if (game.state == PAUSE) {
        Pause_Draw(pause, game_size);
      }
    } else if (current_game_scene == MENU) {
      Menu_Draw(menu, game_size);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}