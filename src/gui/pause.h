#ifndef PAUSE_H
#define PAUSE_H
#include "../game.h"

typedef struct {
  const char        *title;
  const unsigned int tick;
  Vector2D           size;
} Pause;

Pause NewPauseGui(const char *title, Vector2D size);

void Pause_Draw(Pause this, int game_size);

GameState Pause_Cycle(Pause *this);

void Pause_HandleEvent(Pause this, SnakeGame *game, KeyboardKey key);

#endif