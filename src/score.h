#ifndef FLIPTRIS_WINDOW_SCORE
#define FLIPTRIS_WINDOW_SCORE

#include "window.h"

namespace Fliptris {
  namespace Window {
    class Score : public ncurses::Window
    {
    public:
      Score(int nlines, int ncols, int y, int x);
      void add(int lines);
      void Draw();

    private:
      int score, lines;
    };
  }
}

#endif
