//--------------------------------------------------------------
// Fliptris
// ========
//  Tetriminos are the building blocks of tetris games. They
// are made up of four blocks, and are in every permutation
// possible.
//--------------------------------------------------------------
// Copyright (c) 2010 Tim Evans
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//--------------------------------------------------------------
#ifndef FLIPTRIS_TETRIMINO
#define FLIPTRIS_TETRIMINO

#include "window.h"

#define COLOR_ORANGE  8     // rgb(240, 160, 0)
#define COLOR_GREY    9     // rgb(125, 125, 125)

namespace Fliptris {
  class Tetrimino : public ncurses::Renderable {
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
