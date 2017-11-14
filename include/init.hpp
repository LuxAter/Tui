#ifndef TUI_INIT_HPP
#define TUI_INIT_HPP

#include <string>

#include "window/window.hpp"

namespace tui {

  enum ColorSets { NO_COLOR = 0, COLOR_16 = 1, COLOR_256 = 2, TRUE_COLOR = 3 };
  enum InitFlags {
    ECHO = 0,
    NO_ECHO = 1,
    RAW = 2,
    NO_RAW = 3,
    CURSOR = 4,
    NO_CURSOR = 5
  };

  extern tui::Window stdscr;
  extern unsigned int _color_access;
  bool InitTui();
  bool TermTui();
  int HasColor();

  void Clear();

  void Refresh();

  void Print(std::string str, ...);
  void mvPrint(unsigned x, unsigned y, std::string str, ...);

  tui::Window CreateWindow();
  tui::Window CreateWindow(int w, int h);
  tui::Window CreateWindow(int x, int y, int w, int h);

}  // namespace tui

#endif /* ifndef TUI_INIT_HPP */
