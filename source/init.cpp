#include "init.hpp"

#include <stdarg.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string>

#include "terminal/terminal.hpp"
#include "window/window.hpp"

namespace tui {
  tui::Window stdscr;
  unsigned int _color_access = NO_COLOR;
}  // namespace tui

bool tui::InitTui() {
  SaveTerm();
  ClearScreen();
  HasColor();
  struct winsize size;
  ioctl(0, TIOCGWINSZ, &size);
  int w = size.ws_row, h = size.ws_col;
  stdscr = tui::Window(0, 0, w, h);
  stdscr.GetBufferPointer()->SetDisplayBuffer(true);
  return true;
}

bool tui::TermTui() {
  ClearScreen();
  printf("\033[0;0H");
  fflush(stdout);
  RestoreTerm();
  return true;
}

int tui::HasColor() {
  if (getenv("COLORTERM")) {
    const char* env = getenv("COLORTERM");
    std::string color_term(env);
    if (color_term == "truecolor") {
      _color_access = TRUE_COLOR;
    } else {
      printf("Unknown color term: %s", color_term.c_str());
    }
  }
  if (_color_access == NO_COLOR && getenv("TERM")) {
    const char* env = getenv("TERM");
    std::string term(env);
    if (term == "xterm") {
      _color_access = COLOR_256;
    } else if (term == "xterm-256color") {
      _color_access = TRUE_COLOR;
    } else if (term == "linux") {
      _color_access = COLOR_16;
    } else {
      printf("Unknown terminal: %s", term.c_str());
    }
  }
  if (_color_access == NO_COLOR && getenv("CI")) {
    if (getenv("TRAVIS")) {
      _color_access = COLOR_16;
    }
  }
  return _color_access;
}

void tui::Clear() { stdscr.Clear(); }

void tui::Refresh() { stdscr.Refresh(); }

void tui::Print(std::wstring str, ...) {
  va_list args;
  va_start(args, str);
  stdscr.Print(str, args);
  va_end(args);
}

void tui::Print(std::string str, ...) {
  va_list args;
  va_start(args, str);
  stdscr.Print(GetWString(str), args);
  va_end(args);
}

void tui::mvPrint(unsigned x, unsigned y, std::wstring str, ...) {
  va_list args;
  va_start(args, str);
  stdscr.mvPrint(x, y, str, args);
  va_end(args);
}

void tui::mvPrint(unsigned x, unsigned y, std::string str, ...) {
  va_list args;
  va_start(args, str);
  stdscr.mvPrint(x, y, GetWString(str), args);
  va_end(args);
}

std::wstring tui::GetWString(std::string str) {
  std::wstring temp(str.length(), L' ');
  std::copy(str.begin(), str.end(), temp.begin());
  return temp;
}

tui::Window tui::CreateWindow() { return stdscr.CreateWindow(); }

tui::Window tui::CreateWindow(int w, int h) {
  return stdscr.CreateWindow(w, h);
}
tui::Window tui::CreateWindow(int x, int y, int w, int h) {
  return stdscr.CreateWindow(x, y, w, h);
}
