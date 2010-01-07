#include "window.h"

using namespace ncurses;

/**
 * Create a new window nlines high, ncols wide
 * at the location begin_y, begin_x.
 */
void Window::Newwin(int nlines, int ncols, int begin_y, int begin_x)
{
  this->lines = nlines;
  this->cols = ncols;
  this->x = begin_x;
  this->y = begin_y;
  this->win = newwin(nlines, ncols, begin_y, begin_x);
}

Window::Window(int nlines, int ncols, int begin_y, int begin_x)
{
  this->Newwin(nlines, ncols, begin_y, begin_x);
}

/**
 * Delete this window from the screen
 */
Window::~Window()
{
  this->Border();
  this->Refresh();
  delwin(this->win);
}

/**
 * Turn off an previously on attribute in this
 * Window.
 */
void Window::Attroff(int attr)
{
  wattroff(this->win, attr);
}

/**
 * Turn on an attribute in this Window.
 * Acceptable attrs:
 *  A_NORMAL      --  Normal display (no highlight)
 *  A_STANDOUT    --  Best highlighting mode of the terminal.
 *  A_UNDERLINE   --  Underlining
 *  A_REVERSE     --  Reverse video
 *  A_BLINK       --  Blinking
 *  A_DIM         --  Half bright
 *  A_BOLD        --  Extra bright or bold
 *  A_PROTECT     --  Protected mode
 *  A_INVIS       --  Invisible or blank mode
 *  A_ALTCHARSET  --  Alternate character set
 *  A_CHARTEXT    --  Bit-mask to extract a character
 *  COLOR_PAIR(n) --  Color-pair number n
 */
void Window::Attron(int attr)
{
  wattron(this->win, attr);
}

/**
 * Set the border of the screen. Defaults to erasing the
 * box around the window
 */
void Window::Border(char ls, char rs, char ts, char bs,
                    char tl, char tr, char bl, char br)
{
  wborder(this->win, ls, rs, ts, bs, tl, tr, bl, br);
}

/**
 * Create a box around the window.
 * Defaults to ... a box.
 */
void Window::Box(int vertch, int horch)
{
  box(this->win, vertch, horch);
}

/**
 * Clear the window completely
 */
void Window::Clear()
{
  wclear(this->win);
}

/**
 * Erase all points that given by the
 * input vector in the window.
 */
void Window::Erase(ncurses::Renderable* object) 
{
  std::map <std::pair <int, int>, int> points = object->points();
  std::map <std::pair <int, int>, int>::iterator iter;
  
  for (iter = points.begin(); iter != points.end(); ++iter) {
    this->Attron(COLOR_PAIR(0) | A_NORMAL);
    this->Mvprintw(iter->first.first, iter->first.second, " ");
    this->Attroff(COLOR_PAIR(0) | A_NORMAL);
  }
}

/**
 * Changes the attribute at location x, y to have the
 * attributes given. Given -1 as the num argument, it will
 * update to the end of the line
 */
void Window::Mvchgat(int y, int x, int num, short attr, short color)
{
  mvwchgat(this->win, y, x, num, attr, color, NULL);
}

/**
 * Returns whether there was any changes made
 * to the terminal.
 *
bool Window::IsDirty()
{
  return this->dirty;
}*/

/**
 * Move a window to absolute coordinates y, x
 */
void Window::Move(int y, int x)
{
  this->Resize(this->lines, this->cols, y, x);
}

/**
 * Paint an object in a window
 */
void Window::Paint(ncurses::Renderable* object)
{
  object->render(this);
}

/**
 * Print a string (formatted like C printf)
 * at the current cursor position.
 */
int Window::Printw(const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int result = vw_printw(this->win, fmt, args);
  va_end(args);
  this->dirty = true;
  return result;
}

/**
 * Print a string (formatted like C printf)
 * at location y, x.
 */
int Window::Mvprintw(int y, int x, const char * fmt, ... )
{
  va_list args;
  va_start(args, fmt);
  int result = wmove(this->win, y, x);
  if (result == OK) {
    result = vw_printw(this->win, fmt, args);
  }
  va_end(args);
  this->dirty = true;
  return result;
}

/**
 * Refresh the contents of the window
 */
void Window::Refresh()
{
  wrefresh(this->win);
  this->dirty = false;
}

/**
 * Resize the window to be nlines high, ncols wide and at
 * position y, x
 */
void Window::Resize(int nlines, int ncols, int y, int x)
{
  this->Border();
  this->Refresh();
  delwin(this->win);
  this->win = newwin(nlines, ncols, y, x);
  this->lines = nlines;
  this->cols = ncols;
  this->y = y;
  this->x = x;

  this->Draw();
  this->Refresh();
}

/**
 * Return the current width of the window.
 */
int Window::Width()
{
  return this->cols;
}

/**
 * Return the current height of the window.
 */
int Window::Height()
{
  return this->lines;
}

/**
 * Return the current x position
 */
int Window::X()
{
  return getmaxx(this->win);
}

/**
 * Return the current y position
 */
int Window::Y()
{
  return getmaxy(this->win);
}
