#ifndef PAUSE_H
#define PAUSE_H

typedef struct {
  const char *title;
} Pause;

void Pause_Draw(Pause this, int game_size);

Pause NewPauseGui(const char *title);

#endif