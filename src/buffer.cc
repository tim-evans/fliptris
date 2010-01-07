#include "buffer.h"

using namespace Fliptris;

/**
 * Clear a line from the buffer
 */
void Buffer::clear_line(int line)
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

/**
 * Insert a single entry into the buffer
 */
void Buffer::insert(int y, int x, int color)
{
  std::pair<int, int> coord(y, x);
  this->buffer[coord] = color;
  this->lines.insert(std::pair <int, std::pair <int, int> >(y, coord));
}

/**
 * Insert multiple entries into the buffer
 */
void Buffer::insert(std::map <std::pair <int, int>, int>::iterator begin, 
                    std::map <std::pair <int, int>, int>::iterator end) {
  this->buffer.insert(begin, end);

  for (begin; begin != end; ++begin) {
    this->lines.insert(std::pair <int, std::pair <int, int> >(begin->first.first, begin->first));
  }
}

int Buffer::count(int line)
{
  return this->lines.count(line);
}

/**
 * Returns the current (painted) state of the Buffer
 */
std::map <std::pair <int, int>, int> Buffer::points()
{
  return this->last_buffer;
}

/**
 * Returns the new state of the Buffer
 */
std::map <std::pair <int, int>, int> Buffer::new_points()
{
  return this->buffer;
}

/**
 * Called when the Buffer is Painted,
 * renders the buffer to the window and 
 * updates the current state
 */
void Buffer::render(ncurses::Window* win)
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

/**
 * Rollback the buffer to the last state that was valid
 */
void Buffer::rollback()
{
  this->lines = this->last_lines;
  this->buffer = this->last_buffer;
}
