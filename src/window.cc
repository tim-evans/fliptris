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
#include "window.h"

using namespace ncurses;

//--------------------------------------------------------------
// Newwin
//  Create a new window nlines high, ncols wide
// at the location begin_y, begin_x. Has to be called by every
// implementing Window class.
//--------------------------------------------------------------
void
Window::Newwin(int nlines, int ncols, int begin_y, int begin_x)
{
  this->lines = nlines;
  this->cols = ncols;
  this->x = begin_x;
  this->y = begin_y;
  this->win = newwin(nlines, ncols, begin_y, begin_x);
}

//--------------------------------------------------------------
// Window
//  Create a new 'vanilla' Window.
//  Input:
//    nlines    | the number of lines the window should be
//    ncols     | the number of columns the window should be
//    begin_y   | the y position of the window
//    begin_x   | the x position of the window
//--------------------------------------------------------------
Window::Window(int nlines, int ncols, int begin_y, int begin_x)
{
  this->Newwin(nlines, ncols, begin_y, begin_x);
}

//--------------------------------------------------------------
// ~Window
//  Delete this window from the screen.
//--------------------------------------------------------------
Window::~Window()
{
  this->Border();
  this->Refresh();
  delwin(this->win);
}

//--------------------------------------------------------------
// Attroff
//  Turn off an previously on attribute in this
// Window.
//  Input:
//    attr    | the attribute to turn off.
//--------------------------------------------------------------
void
Window::Attroff(int attr)
{
  wattroff(this->win, attr);
}

//--------------------------------------------------------------
// Attron
//  Turn on an attribute in this Window.
//  Input:
//    attr    | the attribute to turn on.
//            | Acceptable attrs:
//            | A_NORMAL
//            |   Normal display (no highlight)
//            | A_STANDOUT
//            |   Best highlighting mode of the terminal.
//            | A_UNDERLINE
//            |   Underlining
//            | A_REVERSE
//            |   Reverse video
//            | A_BLINK
//            |   Blinking
//            | A_DIM
//            |   Half bright
//            | A_BOLD
//            |   Extra bright or bold
//            | A_PROTECT
//            |   Protected mode
//            | A_INVIS
//            |   Invisible or blank mode
//            | A_ALTCHARSET
//            |   Alternate character set
//            | A_CHARTEXT
//            |   Bit-mask to extract a character
//            | COLOR_PAIR(n)
//            |   Color-pair number n
//--------------------------------------------------------------
void
Window::Attron(int attr)
{
  wattron(this->win, attr);
}

//--------------------------------------------------------------
// Border
//  Set the border of the screen. Defaults to erasing the
// box around the window
//  Input:
//    ls      | left side character
//    rs      | right side character
//    ts      | top side character
//    bs      | bottom side character
//    tl      | top left-hand corner character
//    tr      | top right-hand corner character
//    bl      | bottom left-hand corner character
//    br      | bottom right-hand corner character
//--------------------------------------------------------------
void
Window::Border(char ls, char rs, char ts, char bs,
               char tl, char tr, char bl, char br)
{
  wborder(this->win, ls, rs, ts, bs, tl, tr, bl, br);
}

//--------------------------------------------------------------
// Box
//  Create a box around the window.
// Defaults to ... a box.
//  Input:
//    vertch    | the vertical character
//    horch     | the horizontal character
//--------------------------------------------------------------
void
Window::Box(int vertch, int horch)
{
  box(this->win, vertch, horch);
}

//--------------------------------------------------------------
// Clear
//  Clearthe window completely
//--------------------------------------------------------------
void
Window::Clear()
{
  wclear(this->win);
}

//--------------------------------------------------------------
// Erase
//  Erase all points that given by the
// input vector in the window.
//  Input:
//    object    | the object to erase
//--------------------------------------------------------------
void
Window::Erase(ncurses::Renderable* object) 
{
  std::map <std::pair <int, int>, int> points = object->points();
  std::map <std::pair <int, int>, int>::iterator iter;
  
  for (iter = points.begin(); iter != points.end(); ++iter) {
    this->Attron(COLOR_PAIR(0) | A_NORMAL);
    this->Mvprintw(iter->first.first, iter->first.second, " ");
    this->Attroff(COLOR_PAIR(0) | A_NORMAL);
  }
}

//--------------------------------------------------------------
// Mvchgat
//  Changes the attribute at location x, y to have the
// attributes given. Given -1 as the num argument, it will
// update to the end of the line.
//  Input:
//    y         | the y location
//    x         | the x location
//    num       | the number of characters to change
//    attr      | the attribute to change to
//    color     | the color to change to
//--------------------------------------------------------------
void
Window::Mvchgat(int y, int x, int num, short attr, short color)
{
  mvwchgat(this->win, y, x, num, attr, color, NULL);
}

//--------------------------------------------------------------
// IsDirty?
//  Returns whether there was any changes made to the terminal.
//--------------------------------------------------------------
bool
Window::IsDirty()
{
  return this->dirty;
}

//--------------------------------------------------------------
// Move
//  Move a window to absolute coordinates y, x
//  Input:
//    y       | the y location to move to
//    x       | the x location to move to
//--------------------------------------------------------------
void
Window::Move(int y, int x)
{
  this->Resize(this->lines, this->cols, y, x);
}

//--------------------------------------------------------------
// Paint
//  Paint an object in a window
//  Input:
//    object  | the object to render
//--------------------------------------------------------------
void
Window::Paint(ncurses::Renderable* object)
{
  object->render(this);
}

//--------------------------------------------------------------
// Print
//  Print a string (formatted like C printf) at the
// current cursor position.
//  Input:
//    fmt     | the formatting string
//    ...     | the argument strings
//--------------------------------------------------------------
int
Window::Printw(const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int result = vw_printw(this->win, fmt, args);
  va_end(args);
  this->dirty = true;
  return result;
}

//--------------------------------------------------------------
// Mvprintw
//  Print a string (formatted like C printf) at location y, x.
//  Input:
//    y       | the y position to print at
//    x       | the x position to print at
//    fmt     | the formating string
//    ...     | the argument strings
//--------------------------------------------------------------
int
Window::Mvprintw(int y, int x, const char * fmt, ... )
{
  va_list args;
  va_start(args, fmt);
  int result = wmove(this->win, y, x);
  if (result == OK) {
    result = vw_printw(this->win, fmt, args);
  }
  va_end(args);
  this->dirty = true;
  return result;
}

//--------------------------------------------------------------
// Refresh
//  Refresh the contents of the window
//--------------------------------------------------------------
void
Window::Refresh()
{
  wrefresh(this->win);
  this->dirty = false;
}

//--------------------------------------------------------------
// Resize
//  Resize the window to be nlines high, ncols wide and at
// position y, x
//  Input:
//    nlines    | the number of lines to change the height to
//    ncols     | the number of columns to change the width to
//    y         | the y position to move the window to
//    x         | the x position to move the window to
//--------------------------------------------------------------
void
Window::Resize(int nlines, int ncols, int y, int x)
{
  this->Border();
  this->Refresh();
  delwin(this->win);
  this->win = newwin(nlines, ncols, y, x);
  this->lines = nlines;
  this->cols = ncols;
  this->y = y;
  this->x = x;

  this->Draw();
  this->Refresh();
}

//--------------------------------------------------------------
// Width
//  Return the current width of the window.
//--------------------------------------------------------------
int
Window::Width()
{
  return this->cols;
}

//--------------------------------------------------------------
// Height
//  Return the current height of the window.
//--------------------------------------------------------------
int
Window::Height()
{
  return this->lines;
}

//--------------------------------------------------------------
// X
//  Return the current x position
//--------------------------------------------------------------
int
Window::X()
{
  return getmaxx(this->win);
}

//--------------------------------------------------------------
// Y
//  Return the current y position
//--------------------------------------------------------------
int
Window::Y()
{
  return getmaxy(this->win);
}
