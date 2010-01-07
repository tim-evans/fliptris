#ifndef FLIPTRIS_WINDOW_TETRIS
#define FLIPTRIS_WINDOW_TETRIS

#include "game.h"

namespace Fliptris {
  namespace Window {
    class Tetris : public Game
    {
    public:
      Tetris(int nlines, int ncols, int y, int x);
  
    protected:
      void _on_kbhit(int key);
      bool rules();
    }
  }
}

#endif
