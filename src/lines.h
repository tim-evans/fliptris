#ifndef FLIPTRIS_WINDOW_LINES
#define FLIPTRIS_WINDOW_LINES

#include "window.h"

namespace Fliptris {
  namespace Window {
    class Lines : public ncurses::Window
    {
    public:
      Lines(int nlines, int ncols, int y, int x);
      void add(int lines);
      void Draw();
    private:
      int lines;
    };
  }
}

#endif
