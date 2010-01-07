#include "score.h"

using namespace Fliptris;

Window::Score::Score(int nlines, int ncols, int y, int x)
{
  this->Newwin(nlines, ncols, y, x);
  this->score = 0;
  this->lines = 0;
  this->Draw();
  this->Refresh();
}

void Window::Score::add(int lines)
{
  this->lines += lines;

  // Original Nintendo Scoring system
  switch (lines)
  {
    case 0:
      this->score += 0 * (this->lines / 10 + 1);
      break;
    case 1:
      this->score += 40 * (this->lines / 10 + 1);
      break;
    case 2:
      this->score += 100 * (this->lines / 10 + 1);
      break;
    case 3:
      this->score += 300 * (this->lines / 10 + 1);
      break;
    case 4:
      this->score += 1200 * (this->lines / 10 + 1);
      break;
  }

  this->Draw();
  this->Refresh();
}

void Window::Score::Draw()
{
  this->Clear();
  this->Box(0, 0);
  this->Attron(A_BOLD);
  this->Mvprintw(0, 0, "Score");
  this->Attroff(A_BOLD);
  this->Mvprintw(1, 2, "%8d", this->score);
}
