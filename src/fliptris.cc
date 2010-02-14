#include "fliptris.h"

using namespace Fliptris;

void
Fliptris::on_key_down()
{
  this->y++;
}

void
Fliptris::on_key_up()
{
  this->block->rotate();
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
