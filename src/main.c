#include "food.h"
#include "game.h"
#include "gui/game_over.h"
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

int defineTileSize(MapSize map_size_option) {
  if (map_size_option == SIZE_20x20)
    return 20;
  else if (map_size_option == SIZE_25x25)
    return 25;
  else if (map_size_option == SIZE_30x30)
    return 30;
  else if (map_size_option == SIZE_15x15)
    return 15;
  else
    return 20;
}

int main(void) {
  auto     game_window_size = 650;
  auto     window_width     = game_window_size;
  auto     window_height    = game_window_size;
  MapSize  map_size_option  = SIZE_20x20;
  auto     tile_count       = defineTileSize(map_size_option);
  Vector2D max_position     = {tile_count, tile_count};

  GameScene current_game_scene = MENU;

  InitWindow(
    window_width, window_height, "raylib [core] example - basic window");

  auto       menu        = NewMenu("Snake Game!!");
  MenuOption menu_select = NONE;
  auto       game_over_menu =
    NewGameOverMenu("The Game is over", NewVector2D(300, 200));
  auto pause = NewPauseGui("Game is Paused!", NewVector2D(300, 200));

  auto game = InitDefaultGame(game_window_size, tile_count);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    KeyboardKey key = GetKeyPressed();

    if (current_game_scene == GAME) {
      Pause_HandleEvent(pause, &game, key);

      if (game.state == RUNNING) {
        Game_Cycle(&game, key, max_position);

      } else if (game.state == PAUSE) {
        game.state = Pause_Cycle(&pause, key);

      } else if (game.state == OVER) {
        game.state = GameOverMenu_Cycle(&game_over_menu, key);

      } else if (game.state == QUIT) {

        current_game_scene = MENU;
        game.state         = RUNNING;
        Game_Reset(&game);
      }
    } else if (current_game_scene == MENU) {
      menu_select = Menu_Cycle(&menu, key);

      if (menu.page == MENU_MAIN && menu.selected_size != map_size_option) {
        map_size_option = menu.selected_size;
        tile_count      = defineTileSize(map_size_option);
        max_position.x = tile_count, max_position.y = tile_count;

        game = InitDefaultGame(game_window_size, tile_count);
      }

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
        Pause_Draw(pause, game_window_size);
      } else if (game.state == OVER) {
        GameOverMenu_Draw(game_over_menu, game_window_size);
      }

    } else if (current_game_scene == MENU) {
      Menu_Draw(menu, game_window_size);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}