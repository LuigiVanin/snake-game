#include "menu.h"
#include <raylib.h>

Menu NewMenu(const char *title) {
  Menu menu = {
    .title   = title,
    .current = NEW,
    .tick    = 0,
  };

  return menu;
}

Color Menu_CurrentOptionColor(Menu this, MenuOption option) {
  if (option == this.current && this.tick < 20) return WHITE;
  return GRAY;
}

void Menu_Draw(Menu this, int game_size) {
  const char *new_game_text = "New Game";
  const char *options_text  = "Options";
  const char *exit_text     = "Exit";

  // Measure text dimensions
  auto title_dim    = MeasureTextEx(GetFontDefault(), this.title, 30, 2.5);
  auto new_game_dim = MeasureTextEx(GetFontDefault(), new_game_text, 25, 2.1);
  auto options_dim  = MeasureTextEx(GetFontDefault(), options_text, 25, 2.1);
  auto exit_dim     = MeasureTextEx(GetFontDefault(), exit_text, 25, 2.1);

  // Draw full screen background
  DrawRectangle(((float)game_size / 2) - ((float)game_size / 2),
                ((float)game_size / 2) - ((float)game_size / 2),
                game_size,
                game_size,
                BLACK);

  // Draw title
  DrawText(this.title,
           ((float)game_size / 2) - (title_dim.x / 2),
           ((float)game_size / 2) - (title_dim.y * 3),
           30,
           WHITE);

  // Draw menu options using the color function
  DrawText(new_game_text,
           ((float)game_size / 2) - (new_game_dim.x / 2),
           ((float)game_size / 2) - (new_game_dim.y / 2),
           25,
           Menu_CurrentOptionColor(this, NEW));

  DrawText(options_text,
           ((float)game_size / 2) - (options_dim.x / 2),
           ((float)game_size / 2) + (options_dim.y * 1.5),
           25,
           Menu_CurrentOptionColor(this, OPTIONS));

  DrawText(exit_text,
           ((float)game_size / 2) - (exit_dim.x / 2),
           ((float)game_size / 2) + (exit_dim.y * 3.5),
           25,
           Menu_CurrentOptionColor(this, QUIT_GAME));
}

MenuOption Menu_Cycle(Menu *this, KeyboardKey key) {
  this->tick = ((this->tick + 1) % 31);

  if (key == KEY_UP) {
    this->tick    = 0;
    this->current = this->current - 1;
    if ((int)this->current < 0) this->current = 2;

  } else if (key == KEY_DOWN) {
    this->tick    = 0;
    this->current = (this->current + 1) % 3;
  }

  if (key == KEY_ENTER && this->current != NONE) {
    auto to_return = this->current;
    this->current  = NEW;
    return to_return;
  }

  return NONE;
}