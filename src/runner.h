#ifndef FLIPTRIS_RUNNER
#define FLIPTRIS_RUNNER

#include <pthread.h>
#include "game.h"
#include "next.h"
#include "score.h"
#include "lines.h"

namespace Fliptris {
  class Runner {
  public:
    Runner(Window::Game* game, Window::Next* next,
           Window::Score* score, Window::Lines* lines);
    void on_key_pressed(int key);
  private:
    void ticker(void *);
    Tetrimino* active_block;

    Window::Game* game;
    Window::Next* next;
    Window::Score* score;
    Window::Lines* lines;

    pthread gravity;
    pthread_mutex_t gravity_mutex;
  }
}

#endif
