#ifndef FLIPTRIS_WINDOW_TETRIS
#define FLIPTRIS_WINDOW_TETRIS

#include "game.h"

namespace Fliptris {
  namespace Window {
    class Tetris : public Game
    {
    public:
      Tetris(int nlines, int ncols, int y, int x);
      void set_listeners(vector<GameListener> listeners);

    protected:
      void on_key_hit(int key);
      bool rules();
    }
  }
}

#endif
