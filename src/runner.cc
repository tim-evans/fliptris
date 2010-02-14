#include "runner.h"

using namespace Fliptris;

Runner::Runner(Window::Game* game, Window::Next* next,
               Window::Score* score, Window::Lines* lines)
{
  this->game = game;
  this->next = next;
  this->score = score;
  this->lines = lines;

  this->block = this->next->next();
  this->gravity_mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_create(&this->gravity, NULL, &this->ticker, NULL);
}

void
Runner::on_key_pressed(int key)
{
  this->game.key_lookup[key]();

  if (!this->game.is_valid()) {
    this->block->rollback();
    this->game->
  }
}

void
Runner::ticker(void *)
{
  struct timespec delay;
  while (true) {
    pthread_mutex_lock(&this->gravity_mutex);
    delay = this->game->get_delay();
    pthread_mutex_unlock(&this->gravity_mutex);

    nanosleep(&delay, NULL);

    pthread_mutex_lock(&this->gravity_mutex);
    this->on_key_pressed(this->game->GRAVITY_BUTTON);
    pthread_mutex_unlock(&this->gravity_mutex);
  }
}
