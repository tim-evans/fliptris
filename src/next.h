#ifndef FLIPTRIS_WINDOW_NEXT
#define FLIPTRIS_WINDOW_NEXT

#include "factory.h"
#include "window.h"
#include <vector>

namespace Fliptris {
  namespace Window {
    class Next : public ncurses::Window
    {
    public:
      Next(int nlines, int ncols, int y, int x);
      Tetrimino* next();
      void Draw();

    private:
      std::vector<Tetrimino*> blocks;
      Tetriminos::Factory factory;
    };
  }
}

#endif
