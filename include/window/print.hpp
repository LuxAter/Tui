#ifndef TUI_WINDOW_PRINT_HPP
#define TUI_WINDOW_PRINT_HPP

#include <string>

namespace tui {
  void Print(std::string fmt, ...);
  void mvPrint(int x, int y, std::string fmt, ...);
}  // namespace tui

#endif /* ifndef TUI_WINDOW_PRINT_HPP */
