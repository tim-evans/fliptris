#include "next.h"

using namespace Fliptris;

Window::Next::Next(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);
  for (int i = 0; i < 3; i++) {
    this->blocks.insert(this->blocks.begin(), this->factory.next());
  }
  this->Draw();
}

Tetrimino* Window::Next::next()
{
  this->Clear();

  Tetrimino* next = this->blocks.back();
  this->blocks.pop_back();
  this->blocks.insert(this->blocks.begin(), this->factory.next());
  this->Draw();
  this->Refresh();

  return next;
}


void Window::Next::Draw()
{
  // Draw the window and label
  this->Box(0, 0);
  this->Attron(A_BOLD);
  this->Mvprintw(0, 0, "Next");
  this->Refresh();
  this->Attroff(A_BOLD);

  std::vector<Tetrimino*>::iterator iter;

  int i = 2;
  int max_x, min_x;

  // Draw each Tetrimino centered within the Next block window
  for (iter = this->blocks.begin(); iter != this->blocks.end(); ++iter) {
    std::map<std::pair <int, int>, int > points = (*iter)->new_points();
    std::map<std::pair <int, int>, int >::iterator it;

    max_x = -1000; min_x = 1000;
    for (it = points.begin(); it != points.end(); ++it) {
      min_x = (min_x > it->first.second) ? it->first.second : min_x;
      max_x = (max_x < it->first.second) ? it->first.second : max_x;
    }

    int space = this->Width() - (max_x - min_x + 1);
    std::pair <int, int> curs = (*iter)->curs();
    (*iter)->curs_to((i--) * 4 + 1, space / 2 - (min_x - curs.second));
    this->Paint(*iter);
  }
}
