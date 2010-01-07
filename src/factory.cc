#include "factory.h"
#include <algorithm>

using namespace Fliptris;

/**
 * Retrieve the next Tetrimino
 */
Tetrimino* Tetriminos::Factory::next() {
  Tetrimino* block = this->bag.back();

  if (this->bag.size() == 3) {
    add_more();
  }
  this->bag.pop_back();

  return block;
}

/**
 * Add more Tetriminos to the grab bag
 * to provide a good distribution of tetriminos
 */
void Tetriminos::Factory::add_more() {
  std::vector<Tetrimino*> bag;

  bag.push_back(new Tetrimino('I'));
  bag.push_back(new Tetrimino('T'));
  bag.push_back(new Tetrimino('O'));
  bag.push_back(new Tetrimino('S'));
  bag.push_back(new Tetrimino('Z'));
  bag.push_back(new Tetrimino('L'));
  bag.push_back(new Tetrimino('J'));

  this->bag.insert(this->bag.begin(), bag.begin(), bag.end());

  std::random_shuffle(this->bag.begin(), this->bag.end());
}
