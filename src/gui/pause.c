#include "pause.h"
#include <raylib.h>

Pause NewPauseGui(const char *title, Vector2D size) {
  Pause element = {
    .title = title,
    .size  = size,
    .tick  = 0,
  };

  return element;
}

void Pause_Draw(Pause this, int game_size) {
  auto text_dim = MeasureTextEx(GetFontDefault(), this.title, 25, 2.1);

  DrawRectangle(((float)game_size / 2) - (text_dim.x / 2) - 10,
                ((float)game_size / 2) - (text_dim.y / 2) - 10,
                text_dim.x + 20,
                text_dim.y + 20,
                BLACK);

  DrawText(this.title,
           ((float)game_size / 2) - (text_dim.x / 2),
           ((float)game_size / 2) - (text_dim.y / 2),
           25,
           WHITE);
}

GameState Pause_Cycle(Pause *this) {
  return PAUSE;
}

void Pause_HandleEvent(Pause this, SnakeGame *game, KeyboardKey key) {
  if (key == KEY_SPACE) {
    if (game->state == RUNNING)
      game->state = PAUSE;
    else
      game->state = RUNNING;
  }
}
