#ifndef FLIPTRIS_TETRIMINO_FACTORY
#define FLIPTRIS_TETRIMINO_FACTORY

#include "tetriminos.h"
#include <cstdlib>
#include <vector>
#include <ctime>

namespace Fliptris {
  namespace Tetriminos {
    class Factory {
      public:
        Factory() {
          srand(time(NULL));
          this->add_more();
        }

        Tetrimino* next();

      private:
        std::vector<Tetrimino*> bag;
        void add_more();
    };
  }
}

#endif
