#include "fliptris.h"

using namespace Fliptris;

void
Fliptris::on_key_down(Tetrimino* block)
{
  block->y(block->y()++);
}

void
Fliptris::on_key_up(Tetrimino* block)
{
  block->rotate();
}

void
Fliptris::on_key_left(Tetrimino* block)
{
  block->x(block->x() - 2);
}

void
Fliptris::on_key_right(Tetrimino* block)
{
  block->x(block->x() + 2);
}

Fliptris::Fliptris(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);  

  this->key_lookup.insert(std::pair<int, void*>(KEY_UP, this->on_key_up));
  this->key_lookup.insert(std::pair<int, void*>(KEY_DOWN, this->on_key_down));
  this->key_lookup.insert(std::pair<int, void*>(KEY_LEFT, this->on_key_left));
  this->key_lookup.insert(std::pair<int, void*>(KEY_RIGHT, this->on_key_right));
  this->key_lookup.insert(std::pair<int, void*>(' ', this->on_key_spacebar));
}
