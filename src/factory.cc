//--------------------------------------------------------------
// Tetrimino Factory
// =================
//  A factory for creating a randomly distributed set of 
//  Tetriminos without potential clogging that comes with pure
//  'random' picking.
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
#include "factory.h"
#include <algorithm>

using namespace Fliptris;

//--------------------------------------------------------------
// Next
//  Get a random Tetrimino to use.
//--------------------------------------------------------------
Tetrimino*
Tetriminos::Factory::next()
{
  Tetrimino* block = this->bag.back();

  if (this->bag.size() == 3) {      // Too few items,
    add_more();                       // repopulate the bag
  }
  this->bag.pop_back();

  return block;
}

//--------------------------------------------------------------
// Add more
//  Add more Tetriminos to the grab bag to provide a good
//  distribution of tetriminos.
//--------------------------------------------------------------
void
Tetriminos::Factory::add_more()
{
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
