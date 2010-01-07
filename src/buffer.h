#ifndef FLIPTRIS_BUFFER
#define FLIPTRIS_BUFFER

#include "window.h"
#include <map>
#include <utility>

namespace Fliptris {
  class Buffer : public ncurses::Renderable
  {
  public:
    Buffer() { };

    void clear_line(int line);
    void insert(int y, int x, int color);
    void insert(std::map <std::pair <int, int>, int>::iterator begin, 
                std::map <std::pair <int, int>, int>::iterator end);
    int count(int line);

    void render(ncurses::Window* win);
    void rollback();

    std::map <std::pair <int, int>, int> points();
    std::map <std::pair <int, int>, int> new_points();
 
  private:
    std::map <std::pair <int, int>, int> buffer, last_buffer;
    std::multimap <int, std::pair <int, int> > lines, last_lines;
  };
}

#endif
