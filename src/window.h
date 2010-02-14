//--------------------------------------------------------------
// ncurses
// =======
//  A C++ wrapper for the ncurses window object.
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
#ifndef NCURSES_WINDOW
#define NCURSES_WINDOW

#include <map>
#include <utility>
#include <ncurses.h>

namespace ncurses {
  class Renderable;

  class Window
  {
    public:
      Window(int nlines, int ncols, int y, int x);
      ~Window();

      void Attroff(int attr);
      void Attron(int attr);
      void Border(char ls=' ', char rs=' ', char ts=' ', char bs=' ',
                  char tl=' ', char tr=' ', char bl=' ', char br=' ');
      void Box(int vertch, int horch);
      void Clear();
      void Mvchgat(int y, int x, int num, short attr, short color);
      void Move(int y, int x);
      void Erase(Renderable* object);
      void Paint(Renderable* object);
      int Printw(const char * format, ...);
      int Mvprintw(int y, int x, const char * format, ...);
      void Refresh();
      void Resize(int nlines, int ncols, int begin_y, int begin_x);
      int Y();
      int X();
      int Width();
      int Height();
  
      virtual void Draw() { };

    protected:
      Window(void) { };
      void Newwin(int nlines, int ncols, int begin_y, int begin_x);

    private:
      WINDOW* win;
      bool dirty;
      int lines, cols, y, x;
  };

  // Renderable class
  class Renderable {
    public:
      // Returns a vector of all of the coordinates
      // that the object is currently occupying, with
      // their associated color
      virtual std::map < std::pair <int, int>, int> points() { };
  
      // Returns a vector of all of the coordinates
      // the object will occupy on the next render
      virtual std::map < std::pair <int, int>, int> new_points() { };

      // Move the object's cursor to y, x
      void curs_to(int y, int x) { 
        this->y = y;
        this->x = x;
      };

      std::pair <int, int> curs() { 
        return std::make_pair(this->y, this->x);
      };

      // Renders the object to the screen
      virtual void render(Window* win) { };
  
      // Rollback changes made since last render
      virtual void rollback() { };

    protected:
      Renderable() { 
        this->y = 0;
        this->x = 0;
      };
      ~Renderable() { };

      int y, x;
  };
}
#endif
