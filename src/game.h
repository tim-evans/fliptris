#ifndef FLIPTRIS_WINDOW_GAME
#define FLIPTRIS_WINDOW_GAME

#include "window.h"
#include "next.h"
#include "tetriminos.h"
#include "buffer.h"
#include <map>
#include <utility>

namespace Fliptris {
  namespace Window {
    class Game : public ncurses::Window
    {
      public:
        Game(int nlines, int ncols, int y, int x);
        void Draw();
        int add(ncurses::Renderable* block);
        void pause();
        bool is_valid(ncurses::Renderable* block);
        int on_kbhit(int key);
        struct timespec get_delay();

      protected:
        int x, y;
        int level;
        Fliptris::Window::Next* next;
        Tetrimino* block;
        //virtual bool rules(Tetrimino* block) { };
        //virtual void _on_kbhit(int key) { };
        Buffer buffer;
    };
  }
}

#endif
