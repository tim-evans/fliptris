#ifndef FLIPTRIS_GAME_LISTENER
#define FLIPTRIS_GAME_LISTENER

namespace Fliptris {
  class GameListener
  {
  public:
    virtual on_lines_cleared(int lines) { };
  };
}

#endif
