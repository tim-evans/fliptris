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
#include "tetriminos.h"

using namespace Fliptris;

//--------------------------------------------------------------
// Tetrimino
//  Construct a block using the original Tetris colors
//  Inputs:
//    type    | the the shape of the tetrimino
//            | with the following mapping:
//            |      'I/i' -> I block
//            |      'J/j' -> J block
//            |      'L/l' -> L block
//            |      'O/o' -> O block
//            |      'S/s' -> S block
//            |      'T/t' -> T block
//            |      'Z/z' -> Z block
//   color    | the color of the tetrimino
//--------------------------------------------------------------
Tetrimino::Tetrimino(char type, int color)
{
  this->type = type;
  this->rotation = 0;
  this->last_rotation = 0;
  this->rendered = true;

  this->last_y = 0;
  this->last_x = 0;
    
  // Translate the type into a block
  switch (type) {
      case 'i':
      case 'I': this->block[0] = 0x00F0; block[1] = 0x4444;
                this->block[2] = 0x00F0; block[3] = 0x4444;
                this->color = COLOR_CYAN;
                break;
      case 'j':
      case 'J': this->block[0] = 0x08E0; block[1] = 0x044C;
                this->block[2] = 0x00E2; block[3] = 0x0644;
                this->color = COLOR_BLUE;
                break;
      case 'l':
      case 'L': this->block[0] = 0x02E0; block[1] = 0x0C44;
                this->block[2] = 0x00E8; block[3] = 0x0446;
                this->color = COLOR_ORANGE;
                break;
      case 'o':
      case 'O': this->block[0] = 0x0660; block[1] = 0x0660;
                this->block[2] = 0x0660; block[3] = 0x0660;
                this->color = COLOR_YELLOW;
                break;
      case 's':
      case 'S': this->block[0] = 0x06C0; block[1] = 0x08C4;
                this->block[2] = 0x06C0; block[3] = 0x08C4;
                this->color = COLOR_GREEN;
                break;
      case 't':
      case 'T': this->block[0] = 0x04E0; block[1] = 0x04C4;
                this->block[2] = 0x00E4; block[3] = 0x0464;
                this->color = COLOR_MAGENTA;
                break;
      case 'z':
      case 'Z': this->block[0] = 0x0C60; block[1] = 0x04C8;
                this->block[2] = 0x0C60; block[3] = 0x04C8;
                this->color = COLOR_RED;
                break;
  }

  if (color != -1) {
    this->color = color;
  }
}


//--------------------------------------------------------------
// Rotate
//  Rotate the tetrimino in place.
//--------------------------------------------------------------
void
Tetrimino::rotate()
{
  this->rotation = (this->rotation + 1) % 4;
}

//--------------------------------------------------------------
// Points
//  Return the coordinates of the Tetrimino as a vector
// of cartesian coordinates in y, x format (for ncurses)
//--------------------------------------------------------------
std::map <std::pair <int, int>, int>
Tetrimino::points()
{
  std::map <std::pair <int, int>, int> points;

  if (this->rendered) { // Nothing has been rendered yet!
    return points;
  }

  int mask = 0x0001;

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      if ((this->block[this->last_rotation] & mask) != 0) {
        points[std::make_pair(this->last_y + row, this->last_x + col * 2)] = 
          this->color;
        points[std::make_pair(this->last_y + row, this->last_x + col * 2 + 1)] =
          this->color;
      }
      mask = mask << 1;
    }
  }

  return points;
}

//--------------------------------------------------------------
// New_Points
//  Return the coordinates of the Tetrimino as a vector
// of cartesian coordinates in y, x format (for ncurses)
//--------------------------------------------------------------
std::map <std::pair <int, int>, int> Tetrimino::new_points()
{
  std::map <std::pair <int, int>, int> points;

  int mask = 0x0001;

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      if ((this->block[this->rotation] & mask) != 0) {
        points[std::make_pair(this->y + row, this->x + col * 2)] = 
          this->color;
        points[std::make_pair(this->y + row, this->x + col * 2 + 1)] =
          this->color;
      }
      mask = mask << 1;
    }
  }

  return points;
}

//--------------------------------------------------------------
// Render
//  Render the Tetrimino in a window.
//  Inputs:
//    win     | the window to draw the tetrimino in.
//--------------------------------------------------------------
void
Tetrimino::render(ncurses::Window* win)
{
  int toDraw = this->block[this->rotation];
  int mask = 0x0001;
  int row, col;

  init_pair(this->color + 1, this->color, this->color);
  win->Attron(COLOR_PAIR(this->color + 1) | A_BOLD);
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      if ((toDraw & mask) != 0 && this->y + row > 0) {
        win->Mvprintw(this->y + row, this->x + col * 2, " ");
        win->Mvprintw(this->y + row, this->x + col * 2 + 1, " ");
      }
      mask = mask << 1;
    }
  }
  win->Attroff(COLOR_PAIR(this->color + 1) | A_BOLD);

  // Update the block's position
  this->last_rotation = this->rotation;
  this->last_x = this->x;
  this->last_y = this->y;

  win->Refresh();

  this->rendered = false;
}

//--------------------------------------------------------------
// Rollback
//  Return the Tetrimino back to it's old (safe) state.
//--------------------------------------------------------------
void
Tetrimino::rollback()
{
  this->rotation = this->last_rotation;
  this->x = this->last_x;
  this->y = this->last_y;
}
