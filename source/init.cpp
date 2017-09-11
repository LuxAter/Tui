#include "init.hpp"

#include <stdlib.h>
#include <string>

bool tui::InitTui() { return true; }

int tui::HasColor() {
  int color_access = NO_COLOR;
  if (getenv("COLORTERM")) {
    const char* env = getenv("COLORTERM");
    std::string color_term(env);
    if (color_term == "truecolor") {
      color_access = TRUE_COLOR;
    } else {
      printf("Unknown color term: %s", color_term.c_str());
    }
  }
  if (color_access == NO_COLOR && getenv("TERM")) {
    const char* env = getenv("TERM");
    std::string term(env);
    if (term == "xterm") {
      color_access = COLOR_256;
    } else if (term == "xterm-256color") {
      color_access = TRUE_COLOR;
    } else {
      printf("Unknown terminal: %s", term.c_str());
    }
  }
  if (color_access == NO_COLOR && getenv("CI")) {
    if (getenv("TRAVIS")) {
      color_access = COLOR_16;
    }
  }
  return color_access;
}
