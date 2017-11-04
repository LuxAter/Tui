#include "init.hpp"

#include <stdlib.h>
#include <string>

#include "output/buffer.hpp"
#include "terminal/terminal.hpp"

namespace tui {
  unsigned int _color_access = NO_COLOR;
}  // namespace tui

bool tui::InitTui() {
  SaveTerm();
  Clear();
  BufferInit();
  HasColor();
  return true;
}

bool tui::TermTui() {
  Clear();
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
