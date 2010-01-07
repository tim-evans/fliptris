#ifndef FLIPTRIS_TETRIMINO
#define FLIPTRIS_TETRIMINO

#include "window.h"

#define COLOR_ORANGE  8     // rgb(240, 160, 0)
#define COLOR_GREY    9     // rgb(125, 125, 125)

namespace Fliptris {
  class Tetrimino : public ncurses::Renderable
  {
  public:
    Tetrimino(char type, int color = -1);
    void rotate();                // rotate the block
    void render(ncurses::Window* win);
    void rollback();

    std::map <std::pair <int, int>, int> points();
    std::map <std::pair <int, int>, int> new_points();

  private:
    void init(char type, bool colored);
    char type;                    // block type (for debugging purposes)
    int color;                    // color of the block
    int rotation, last_rotation;
    bool rendered;
    int block[4];
    int last_x, last_y;
  };
}
#endif
