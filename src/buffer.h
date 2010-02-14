//--------------------------------------------------------------
// Fliptris
// ========
//  The buffer to draw static elements in the playing board.
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
#ifndef FLIPTRIS_BUFFER
#define FLIPTRIS_BUFFER

#include "window.h"
#include <map>
#include <utility>

namespace Fliptris {
  class Buffer : public ncurses::Renderable {
    public:
      Buffer() { };

      void clear_line(int line);
      void insert(int y, int x, int color);
      void insert(std::map <std::pair <int, int>, int>::iterator begin, 
                  std::map <std::pair <int, int>, int>::iterator end);
      int count(int line);

      void render(ncurses::Window* win);
      void rollback();

      std::map <std::pair <int, int>, int> points();
      std::map <std::pair <int, int>, int> new_points();
 
    private:
      std::map <std::pair <int, int>, int> buffer, last_buffer;
      std::multimap <int, std::pair <int, int> > lines, last_lines;
  };
}

#endif
