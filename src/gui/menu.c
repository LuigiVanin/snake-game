#include "menu.h"
#include <raylib.h>

Menu NewMenu(const char *title) {
  Menu menu = {
    .title          = title,
    .current        = NEW,
    .tick           = 0,
    .page           = MENU_MAIN,
    .current_option = OPTION_SIZE,
    .selected_size  = SIZE_20x20,
  };

  return menu;
}

Color Menu_CurrentOptionColor(Menu this, MenuOption option) {
  if (option == this.current && this.tick < 20) return WHITE;
  return GRAY;
}

void Menu_Draw(Menu this, int game_size) {

  if (this.page == MENU_MAIN) {

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
  } else if (this.page == MENU_OPTIONS) {

    const char *options_title = "Options";
    const char *size_label    = "Map Size:";
    const char *back_text     = "Back";

    // Size option strings
    const char *size_options[] = {"15x15", "20x20", "25x25", "30x30"};

    // Measure text dimensions
    auto options_title_dim =
      MeasureTextEx(GetFontDefault(), options_title, 30, 2.5);
    auto size_label_dim = MeasureTextEx(GetFontDefault(), size_label, 25, 2.1);
    auto back_dim       = MeasureTextEx(GetFontDefault(), back_text, 25, 2.1);

    // Draw full screen background
    DrawRectangle(0, 0, game_size, game_size, BLACK);

    // Draw title
    DrawText(options_title,
             ((float)game_size / 2) - (options_title_dim.x / 2),
             ((float)game_size / 2) - (options_title_dim.y * 4),
             30,
             WHITE);

    // Determine colors based on selection
    Color size_color =
      (this.current_option == OPTION_SIZE && this.tick < 20) ? WHITE : GRAY;
    Color back_color =
      (this.current_option == OPTION_BACK && this.tick < 20) ? WHITE : GRAY;

    // Draw "Map Size:" label
    DrawText(size_label,
             ((float)game_size / 2) - (size_label_dim.x / 2),
             ((float)game_size / 2) - (size_label_dim.y * 1.5),
             25,
             size_color);

    // Draw size options with arrows
    const char *current_size = size_options[this.selected_size];
    auto        size_value_dim =
      MeasureTextEx(GetFontDefault(), current_size, 25, 2.1);

    // Draw left arrow, current size, and right arrow
    float size_y =
      ((float)game_size / 2) - (size_label_dim.y * 1.5) + size_label_dim.y + 15;

    if (this.current_option == OPTION_SIZE) {
      DrawText("<",
               ((float)game_size / 2) - size_value_dim.x - 30,
               size_y,
               25,
               size_color);
    }

    DrawText(current_size,
             ((float)game_size / 2) - (size_value_dim.x / 2),
             size_y,
             25,
             size_color);

    if (this.current_option == OPTION_SIZE) {
      DrawText(">",
               ((float)game_size / 2) + size_value_dim.x + 10,
               size_y,
               25,
               size_color);
    }

    // Draw "Back" option
    DrawText(back_text,
             ((float)game_size / 2) - (back_dim.x / 2),
             ((float)game_size / 2) + (back_dim.y * 2.5),
             25,
             back_color);
  }
}

MenuOption Menu_Cycle(Menu *this, KeyboardKey key) {
  this->tick = ((this->tick + 1) % 31);

  if (this->page == MENU_OPTIONS) {
    if (key == KEY_UP) {
      this->tick           = 0;
      this->current_option = this->current_option - 1;
      if ((int)this->current_option < 0) this->current_option = OPTION_BACK;

    } else if (key == KEY_DOWN) {
      this->tick           = 0;
      this->current_option = (this->current_option + 1) % 2;
    }

    if (this->current_option == OPTION_SIZE) {
      if (key == KEY_LEFT) {
        this->tick          = 0;
        this->selected_size = this->selected_size - 1;
        if ((int)this->selected_size < 0) this->selected_size = SIZE_30x30;
      } else if (key == KEY_RIGHT) {
        this->tick          = 0;
        this->selected_size = (this->selected_size + 1) % 4;
      }
    }

    if (key == KEY_ENTER) {
      this->page           = MENU_MAIN;
      this->current_option = OPTION_SIZE;
    }

    return NONE;
  }

  // Handle main menu navigation
  if (key == KEY_UP) {
    this->tick    = 0;
    this->current = this->current - 1;
    if ((int)this->current < 0) this->current = 2;

  } else if (key == KEY_DOWN) {
    this->tick    = 0;
    this->current = (this->current + 1) % 3;
  }

  if (key == KEY_ENTER && this->current == OPTIONS) {
    this->page = MENU_OPTIONS;
    return NONE;
  }

  if (key == KEY_ENTER && this->current != NONE) {
    auto to_return = this->current;
    this->current  = NEW;
    return to_return;
  }

  return NONE;
}