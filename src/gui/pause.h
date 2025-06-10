#ifndef PAUSE_H
#define PAUSE_H
#include "../game.h"

typedef struct {
  const char *title;
  const int   tick;
} Pause;

Pause NewPauseGui(const char *title);

void Pause_Draw(Pause this, int game_size);

GameState Pause_Cycle(Pause *this);

GameState Pause_HandleEvent(Pause this, KeyboardKey key, GameState state);

#endif