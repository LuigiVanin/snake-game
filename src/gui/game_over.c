#include "game_over.h"
#include <raylib.h>
#include <stdlib.h>

GameOverMenu NewGameOverMenu(const char *title, Vector2D size) {
  GameOverMenu menu = {
    .size  = size,
    .title = title,
    .tick  = 0,
  };

  return menu;
}

Color GameOverMenu_CurrentOptionColor(GameOverMenu this,
                                      GameOverOptionIndex option) {
  if (option == this.current && this.tick < 20) return WHITE;
  return GRAY;
}

void GameOverMenu_Draw(GameOverMenu this, int game_size) {
  auto border_margin = 5;

  const char *text_menu = "Back to Menu";
  const char *text_exit = "Rage Quit";

  DrawRectangle(((float)game_size / 2) - ((float)this.size.x / 2),
                ((float)game_size / 2) - ((float)this.size.y / 2),
                this.size.x,
                this.size.y,
                BLACK);

  DrawRectangleLines(
    ((float)game_size / 2) - ((float)this.size.x / 2) - border_margin,
    ((float)game_size / 2) - ((float)this.size.y / 2) - border_margin,
    this.size.x + (border_margin * 2),
    this.size.y + (border_margin * 2),
    WHITE);

  auto text_dim = MeasureTextEx(GetFontDefault(), this.title, 25, 2.1);

  DrawText(this.title,
           ((float)game_size / 2) - (text_dim.x / 2),
           ((float)(game_size - this.size.y) / 2) + (1.5 * text_dim.y),
           25,
           WHITE);

  text_dim = MeasureTextEx(GetFontDefault(), text_menu, 25, 2.1);

  DrawText(text_menu,
           ((float)game_size / 2) - (text_dim.x / 2),
           ((float)(game_size - this.size.y) / 2) + (4 * text_dim.y),
           25,
           GameOverMenu_CurrentOptionColor(this, BACK_TO_MENU));

  text_dim = MeasureTextEx(GetFontDefault(), text_exit, 25, 2.1);

  DrawText(text_exit,
           ((float)game_size / 2) - (text_dim.x / 2),
           ((float)(game_size - this.size.y) / 2) + (5.25 * text_dim.y),
           25,
           GameOverMenu_CurrentOptionColor(this, RAGEQUIT));
}

GameState GameOverMenu_Cycle(GameOverMenu *this, KeyboardKey key) {
  this->tick = (this->tick + 1) % 31;

  if (key == KEY_DOWN) {
    this->current = this->current - 1;
    if ((int)this->current < 0) this->current = 1;

  } else if (key == KEY_UP)
    this->current = (this->current + 1) % 2;

  if (key == KEY_ENTER && this->current == RAGEQUIT) {
    CloseWindow();
    exit(0);
  } else if (key == KEY_ENTER && this->current == BACK_TO_MENU) {
    return QUIT;
  }

  return OVER;
}