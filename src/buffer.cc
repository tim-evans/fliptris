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
#include "buffer.h"

using namespace Fliptris;

//--------------------------------------------------------------
// Clear Line
//  Clear a line from the buffer (a line has been cleared)
//  Input:
//    line      | the line to clear.
//--------------------------------------------------------------
void
Buffer::clear_line(int line)
{
  std::pair <std::multimap <int, std::pair <int, int> >::iterator,
             std::multimap <int, std::pair <int, int> >::iterator> ret;
  std::multimap <int, std::pair <int, int> >::iterator iter;

  ret = this->lines.equal_range(line);
  for (iter = ret.first; iter != ret.second; ++iter) {
    this->buffer.erase(iter->second);
  }
  this->lines.erase(line);
}

//--------------------------------------------------------------
// Insert
//  Insert a single entry into the buffer
//  Input:
//    y       | the y position of the thing to insert
//    x       | the x position of the thing to insert
//    color   | the color of the block
//--------------------------------------------------------------
void
Buffer::insert(int y, int x, int color)
{
  std::pair<int, int> coord(y, x);
  this->buffer[coord] = color;
  this->lines.insert(std::pair <int, std::pair <int, int> >(y, coord));
}

//--------------------------------------------------------------
// Insert
//  Insert multiple entries into the buffer
//  Input:
//    begin   | the iterator at the beginning
//    end     | the iterator at the end
//--------------------------------------------------------------
void
Buffer::insert(std::map <std::pair <int, int>, int>::iterator begin, 
               std::map <std::pair <int, int>, int>::iterator end) {
  this->buffer.insert(begin, end);

  for (begin; begin != end; ++begin) {
    this->lines.insert(std::pair <int, std::pair <int, int> >(begin->first.first, begin->first));
  }
}

//--------------------------------------------------------------
// Count
//  The number of elements in the specified line.
//  Input:
//    line    | the line to check.
//--------------------------------------------------------------
int
Buffer::count(int line)
{
  return this->lines.count(line);
}

//--------------------------------------------------------------
// Points
//  Returns the current (painted) state of the Buffer
//--------------------------------------------------------------
std::map <std::pair <int, int>, int>
Buffer::points()
{
  return this->last_buffer;
}

//--------------------------------------------------------------
// New Points
//  Returns the new state of the Buffer (undrawn).
//--------------------------------------------------------------
std::map <std::pair <int, int>, int>
Buffer::new_points()
{
  return this->buffer;
}

//--------------------------------------------------------------
// Render
//  Called when the Buffer is Painted, renders the buffer to
// the window and updates the current state.
//  Input:
//    win     | the window to render the buffer in
//--------------------------------------------------------------
void
Buffer::render(ncurses::Window* win)
{
  std::map <std::pair <int, int>, int>::iterator iter;
  for (iter = this->buffer.begin(); iter != this->buffer.end(); ++iter) {
    win->Attron(COLOR_PAIR((*iter).second + 1) | A_BOLD);
    win->Mvprintw((*iter).first.first, (*iter).first.second, " ");
    win->Attroff(COLOR_PAIR((*iter).second + 1) | A_BOLD);
  }

  this->last_lines = this->lines;
  this->last_buffer = this->buffer;
}

//--------------------------------------------------------------
// Rollback
//  Rollback the buffer to the last state that was valid.
//--------------------------------------------------------------
void
Buffer::rollback()
{
  this->lines = this->last_lines;
  this->buffer = this->last_buffer;
}
