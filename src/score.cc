//--------------------------------------------------------------
// Fliptris
// ========
//  Score window displaying the current score.
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
#include "score.h"

using namespace Fliptris;

//--------------------------------------------------------------
// Score constructor
//  Create a new window for the score window to live in.
//  Input:
//    nlines    | the number of lines the window should be
//    nclos     | the number of columns the window should be
//    y         | the y-position of the window
//    x         | the x-position of the window
//--------------------------------------------------------------
Window::Score::Score(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);
  this->score = 0;
  this->lines = 0;
  this->Draw();
  this->Refresh();
}

//--------------------------------------------------------------
// Add
//  Add some lines to the current tally.
//  Input:
//    lines     | the number of lines to add that have been
//              | cleared
//--------------------------------------------------------------
void
Window::Score::add(int lines)
{
  this->lines += lines;

  // Original Nintendo Scoring system
  switch (lines)
  {
    case 0:
      this->score += 0 * (this->lines / 10 + 1);
      break;
    case 1:
      this->score += 40 * (this->lines / 10 + 1);
      break;
    case 2:
      this->score += 100 * (this->lines / 10 + 1);
      break;
    case 3:
      this->score += 300 * (this->lines / 10 + 1);
      break;
    case 4:
      this->score += 1200 * (this->lines / 10 + 1);
      break;
  }

  this->Draw();
  this->Refresh();
}

//--------------------------------------------------------------
// Draw
//  Redraw the window as if everything went wrong.
//--------------------------------------------------------------
void
Window::Score::Draw()
{
  this->Clear();
  this->Box(0, 0);
  this->Attron(A_BOLD);
  this->Mvprintw(0, 0, "Score");
  this->Attroff(A_BOLD);
  this->Mvprintw(1, 2, "%8d", this->score);
}
