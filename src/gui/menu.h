#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef enum {
  NONE      = -1,
  NEW       = 0,
  OPTIONS   = 1,
  QUIT_GAME = 2,
} MenuOption;

typedef struct {
  const char  *title;
  unsigned int tick;
  // MenuOption   selected;
  MenuOption current;
} Menu;

void Menu_Draw(Menu this, int game_size);

Menu NewMenu(const char *title);

MenuOption Menu_Cycle(Menu *menu, KeyboardKey key);

#endif