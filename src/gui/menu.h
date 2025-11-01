#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef enum {
  NONE      = -1,
  NEW       = 0,
  OPTIONS   = 1,
  QUIT_GAME = 2,
} MenuOption;

typedef enum {
  SIZE_15x15 = 0,
  SIZE_20x20 = 1,
  SIZE_25x25 = 2,
  SIZE_30x30 = 3,
} MapSize;

typedef enum {
  OPTION_SIZE = 0,
  OPTION_BACK = 1,
} OptionsMenuOption;

typedef enum {
  MENU_MAIN,
  MENU_OPTIONS,
} MenuPage;

typedef struct {
  const char  *title;
  unsigned int tick;
  MenuPage     page;
  // MenuOption   selected;
  MenuOption        current;
  OptionsMenuOption current_option;
  MapSize           selected_size;
} Menu;

void Menu_Draw(Menu this, int game_size);

Menu NewMenu(const char *title);

MenuOption Menu_Cycle(Menu *menu, KeyboardKey key);

#endif