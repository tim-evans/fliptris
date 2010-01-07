#include "lines.h"

using namespace Fliptris;

Window::Lines::Lines(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);
  this->lines = 0;
  this->Draw();
  this->Refresh();
}

void Window::Lines::add(int lines)
{
  this->lines += lines;
  this->Draw();
  this->Refresh();
}

void Window::Lines::Draw()
{
  this->Box(0, 0);
  this->Attron(A_BOLD);
  this->Mvprintw(0, 0, "Lines");
  this->Attroff(A_BOLD);
  this->Mvprintw(1, 2, "%8d", this->lines);
}
