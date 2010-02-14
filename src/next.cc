//--------------------------------------------------------------
// Fliptris
// ========
//  Next window displaying the next few blocks to fall.
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
#include "next.h"

using namespace Fliptris;

//--------------------------------------------------------------
// Next constructor
//  Create a new window for the score window to live in.
//  Input:
//    nlines    | the number of lines the window should be
//    nclos     | the number of columns the window should be
//    y         | the y-position of the window
//    x         | the x-position of the window
//--------------------------------------------------------------
Window::Score::Score(int nlines, int ncols, int y, int x)
Window::Next::Next(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);
  for (int i = 0; i < 3; i++) {
    this->blocks.insert(this->blocks.begin(), this->factory.next());
  }
  this->Draw();
}

//--------------------------------------------------------------
// Next
//  Return the next block in the window, and update the window.
//  Output:
//    The next tetrimino to drop into the game.
//--------------------------------------------------------------
Tetrimino*
Window::Next::next()
{
  this->Clear();

  Tetrimino* next = this->blocks.back();
  this->blocks.pop_back();
  this->blocks.insert(this->blocks.begin(), this->factory.next());
  this->Draw();
  this->Refresh();

  return next;
}


//--------------------------------------------------------------
// Draw
//  Redraw the window as if everything went wrong.
//--------------------------------------------------------------
void
Window::Next::Draw()
{
  // Draw the window and label
  this->Box(0, 0);
  this->Attron(A_BOLD);
  this->Mvprintw(0, 0, "Next");
  this->Refresh();
  this->Attroff(A_BOLD);

  std::vector<Tetrimino*>::iterator iter;

  int i = 2;
  int max_x, min_x;

  // Draw each Tetrimino centered within the Next block window
  for (iter = this->blocks.begin(); iter != this->blocks.end(); ++iter) {
    std::map<std::pair <int, int>, int > points = (*iter)->new_points();
    std::map<std::pair <int, int>, int >::iterator it;

    max_x = -1000; min_x = 1000;
    for (it = points.begin(); it != points.end(); ++it) {
      min_x = (min_x > it->first.second) ? it->first.second : min_x;
      max_x = (max_x < it->first.second) ? it->first.second : max_x;
    }

    int space = this->Width() - (max_x - min_x + 1);
    std::pair <int, int> curs = (*iter)->curs();
    (*iter)->curs_to((i--) * 4 + 1, space / 2 - (min_x - curs.second));
    this->Paint(*iter);
  }
}
