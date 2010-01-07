#include "next.h"
#include "score.h"
#include "lines.h"
#include "game.h"

#include <ncurses.h>
#include <sys/signal.h>
#include <unistd.h>
#include <pthread.h>

#define COLOR_ORANGE 8

using namespace Fliptris;

Tetrimino* block;
Window::Game* game;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *tick(void* args)
{
  struct timespec delay;
  while (true) {
    pthread_mutex_lock(&mutex);
    delay = game->get_delay();
    pthread_mutex_unlock(&mutex);

    nanosleep(&delay, NULL);

    pthread_mutex_lock(&mutex);
    game->on_kbhit(KEY_DOWN);
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char *argv[])
{
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  refresh();

  use_default_colors();
  start_color();
  if (can_change_color) {
    init_color(COLOR_RED, 941, 0, 0);
    init_color(COLOR_ORANGE, 941, 627, 0);
    init_color(COLOR_YELLOW, 941, 941, 0);
    init_color(COLOR_GREEN, 0, 941, 0);
    init_color(COLOR_CYAN, 0, 941, 941);
    init_color(COLOR_BLUE, 0, 0, 941);
    init_color(COLOR_MAGENTA, 627, 0, 627);
    init_color(COLOR_GREY, 490, 490, 490);
  }

  Window::Score* score = new Window::Score(3, 12, 1, COLS / 2 + 5);
  Window::Lines* lines = new Window::Lines(3, 12, 4, COLS / 2 + 5);
  game = new Window::Game(20, 22, 1, COLS / 2 - 17);

  int key;
  pthread_t pid;
  pthread_create(&pid, NULL, &tick, NULL);

  while ((key = getch()) != 'q') {

    switch(key)
    {
      case KEY_RESIZE:
        pthread_mutex_lock(&mutex);
        game->Move(1, COLS / 2 - 17);
        pthread_mutex_unlock(&mutex);
        score->Move(1, COLS / 2 + 5);
        lines->Move(4, COLS / 2 + 5);
        refresh();
        break;
      default:
        pthread_mutex_lock(&mutex);
        int cleared = game->on_kbhit(key);
        pthread_mutex_unlock(&mutex);
        score->add(cleared);
        lines->add(cleared);
    }
  }

  delete score;
  delete lines;
  endwin();
  pthread_kill(pid, NULL);
  return 0;
}
