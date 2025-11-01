#include "../game.h"

typedef enum {
  BACK_TO_MENU = 0,
  RAGEQUIT     = 1,
} GameOverOptionIndex;

typedef struct {
  Vector2D            size;
  const char         *title;
  unsigned int        tick;
  GameOverOptionIndex current;

} GameOverMenu;

GameOverMenu NewGameOverMenu(const char *title, Vector2D size);

void GameOverMenu_Draw(GameOverMenu this, int game_size);

GameState GameOverMenu_Cycle(GameOverMenu *this, KeyboardKey key);