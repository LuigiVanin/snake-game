#include "pause.h"
#include <raylib.h>

Pause NewPauseGui(const char *title) {
  Pause element = {.title = title};

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

GameState Pause_HandleEvent(Pause this, KeyboardKey key, GameState state) {
  if (key == KEY_SPACE) {
    if (state == RUNNING)
      return PAUSE;
    else
      return RUNNING;
  }
  return state;
}
