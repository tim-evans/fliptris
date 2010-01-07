#include "game.h"

using namespace Fliptris;

Window::Game::Game(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);
  this->Draw();
  this->Refresh();
  int col = 0, line;
  for (line = 0; line < nlines; line++)
    this->buffer.insert(line, col, COLOR_PAIR(0));

  line = nlines - 1;
  for (col = 0; col < ncols; col++)
    this->buffer.insert(line, col, COLOR_PAIR(0));

  col = ncols;
  for (line = 0; line < nlines; line++)
    this->buffer.insert(line, col, COLOR_PAIR(0));

  this->x = 7;
  this->y = 0;
  this->level = 1;
  this->next = new Fliptris::Window::Next(14, 12, 7, COLS / 2 + 5);
  this->block = this->next.next();
  this->block->curs_to(0, 7);
  this->Paint(this->block);
}

void Window::Game::pause()
{
  Window* win = new Window(3, 7, this->Y() + this->Height() / 2 - 2,
                                 this->X() + this->Width() / 2 - 3);
  win->Box(0, 0);
  win->Mvprintw(1, 1, "Pause");
  win->Refresh();
  refresh();

  int key;
  while (key != 'p')
    key = getch();

  win->Clear();
  delete win;
}

int Window::Game::add(ncurses::Renderable* block)
{
  std::map <std::pair <int, int>, int> points = block->points();
  std::map <std::pair <int, int>, int>::iterator iter;

  this->buffer.insert(points.begin(), points.end()); 

  int cleared = 0;

  for (int line = this->Height() - 2; line > 0; line--) {
    if (this->buffer.count(line) == 20) {
      this->buffer.clear_line(line);
      cleared++;
    }
  }

  this->Erase(&this->buffer);
  this->Paint(&this->buffer);

  return cleared;
}

bool Window::Game::is_valid(ncurses::Renderable* block)
{
  std::map <std::pair <int, int>, int> points = block->new_points();
  std::map <std::pair <int, int>, int>::iterator iter;

  for (iter = points.begin(); iter != points.end(); ++iter) {
    if (this->buffer.new_points().count(iter->first) > 0) {
      block->rollback();
//      this->buffer.rollback();
      return false;
    }
  }
  return true;
}

void Window::Game::Draw()
{
  this->Box(0, 0);
  this->Paint(&this->buffer);
}

struct timespec Window::Game::get_delay()
{
  struct timespec delay = {0, (11 - this->level / 10) * 0.05 * 1000000000};
  return delay;
}

int Window::Game::on_kbhit(int key)
{
  switch (key) {
    case KEY_UP:
      block->rotate();
      break;
    case KEY_DOWN:
      this->y++;
      break;
    case KEY_LEFT:
      this->x -= 2;
      break;
    case KEY_RIGHT:
      this->x += 2;
      break;
    case 'p':
      this->pause();
      break;
    case ' ':
      while (this->is_valid(block)) {
        this->y++;
        this->Erase(block);
        this->Paint(block);
        block->curs_to(this->y, this->x);
      }
      this->y++;
      break;
    default:
      break;
//      this->_on_kbhit(key);
  }

  int cleared = 0;
  if (key != ' ') {
    this->Erase(block);
    this->Box(0, 0);
  }

  block->curs_to(this->y, this->x);
  if (!this->is_valid(block)) {
    std::pair<int, int> cursor = block->curs();
    this->y = cursor.first;
    this->x = cursor.second;
    if (key == KEY_DOWN) {
      this->Paint(block);
      cleared = this->add(block);
      this->level += cleared;
      block = next->next();
      this->x = 7;
      this->y = 0;
      block->curs_to(this->y, this->x);
    }
  }
  this->Paint(block);
  this->Refresh();

  return cleared;
}
