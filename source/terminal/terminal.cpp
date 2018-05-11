#include "terminal/terminal.hpp"

#include <stdio.h>
#include <termios.h>

#include "terminal/cursor.hpp"

namespace tui {
  static struct termios base_term_;
  static bool echo_ = true, cursor_ = true, raw_ = false;
}  // namespace tui

void tui::SaveTerm() { tcgetattr(0, &base_term_); }

void tui::RestoreTerm() { tcsetattr(0, TCSANOW, &base_term_); }

void tui::Echo() {
  struct termios term;
  tcgetattr(0, &term);
  term.c_lflag |= ECHO;
  tcsetattr(0, TCSANOW, &term);
  echo_ = true;
}

void tui::NoEcho() {
  struct termios term;
  tcgetattr(0, &term);
  term.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &term);
  echo_ = false;
}

void tui::Cursor() {
  printf("\033[?25h\n");
  cursor_ = true;
}

void tui::NoCursor() {
  printf("\033[?25l\n");
  cursor_ = false;
}

void tui::Raw() {
  struct termios term;
  tcgetattr(0, &term);
  term.c_lflag &= ~ICANON;
  tcsetattr(0, TCSANOW, &term);
  raw_ = true;
}

void tui::NoRaw() {
  struct termios term;
  tcgetattr(0, &term);
  term.c_lflag |= ICANON;
  tcsetattr(0, TCSANOW, &term);
  raw_ = false;
}

void tui::ClearScreen() {
  printf("\033[2J\n");
  SetCursor(0, 0);
}

void tui::ClearLine() {
  printf("\033[2K\n");
  SetCursor(0, -1);
}
