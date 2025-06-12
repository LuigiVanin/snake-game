#ifndef PAUSE_H
#define PAUSE_H
#include "../game.h"

typedef enum {
  RESUME = 0,
  EXIT   = 1,
} PauseOptionIndex;

typedef struct {
  const char      *title;
  unsigned int     tick;
  PauseOptionIndex current;
  Vector2D         size;
} Pause;

Pause NewPauseGui(const char *title, Vector2D size);

void Pause_Draw(Pause this, int game_size);

GameState Pause_Cycle(Pause *this, KeyboardKey key);

void Pause_HandleEvent(Pause this, SnakeGame *game, KeyboardKey key);

#endif