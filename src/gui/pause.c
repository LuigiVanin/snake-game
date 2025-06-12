#include "pause.h"
#include <raylib.h>

Pause NewPauseGui(const char *title, Vector2D size) {
  Pause element = {
    .title   = title,
    .size    = size,
    .tick    = 0,
    .current = 0,
  };

  return element;
}

Color Pause_CurrentOptionColor(Pause this, PauseOptionIndex option) {
  if (option == this.current && this.tick < 20) return WHITE;
  return GRAY;
}

void Pause_Draw(Pause this, int game_size) {
  const char *text_resume = "Resume";
  const char *text_exit   = "Quit";
  auto        text_dim = MeasureTextEx(GetFontDefault(), this.title, 25, 2.1);

  auto text_resume_dim = MeasureTextEx(GetFontDefault(), text_resume, 25, 2.1);
  auto text_exit_dim   = MeasureTextEx(GetFontDefault(), text_exit, 25, 2.1);

  auto border_margin = 5;

  DrawRectangle(((float)game_size / 2) - ((float)this.size.x / 2),
                ((float)game_size / 2) - ((float)this.size.y / 2),
                this.size.x,
                this.size.y,
                BLACK);

  DrawRectangleLines(
    ((float)game_size / 2) - ((float)this.size.x / 2) - border_margin,
    ((float)game_size / 2) - ((float)this.size.y / 2) - border_margin,
    this.size.x + (border_margin * 2),
    this.size.y + (border_margin * 2),
    WHITE);

  DrawText(this.title,
           ((float)game_size / 2) - (text_dim.x / 2),
           ((float)(game_size - this.size.y) / 2) + (1.5 * text_dim.y),
           25,
           WHITE);

  DrawText(text_resume,
           ((float)game_size / 2) - (text_resume_dim.x / 2),
           ((float)(game_size - this.size.y) / 2) + (4 * text_dim.y),
           25,
           Pause_CurrentOptionColor(this, RESUME));

  DrawText(text_exit,
           ((float)game_size / 2) - (text_exit_dim.x / 2),
           ((float)(game_size - this.size.y) / 2) + (5.25 * text_dim.y),
           25,
           Pause_CurrentOptionColor(this, EXIT));
}

GameState Pause_Cycle(Pause *this, KeyboardKey key) {
  this->tick = (this->tick + 1) % 31;

  if (key == KEY_DOWN) {
    this->current = this->current - 1;
    if ((int)this->current < 0) this->current = 1;

  } else if (key == KEY_UP)
    this->current = (this->current + 1) % 2;

  if (key == KEY_ENTER && this->current == RESUME) {
    return RUNNING;
  } else if (key == KEY_ENTER && this->current == EXIT) {
    return QUIT;
  }

  return PAUSE;
}

void Pause_HandleEvent(Pause this, SnakeGame *game, KeyboardKey key) {
  if (key == KEY_SPACE) {
    if (game->state == RUNNING)
      game->state = PAUSE;
    else
      game->state = RUNNING;

    return;
  }
}
