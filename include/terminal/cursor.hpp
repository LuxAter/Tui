#ifndef TUI_TERMINAL_CURSOR_HPP
#define TUI_TERMINAL_CURSOR_HPP

namespace tui {
  static int cursor_position_[2] = {0, 0};

  void GetCursor(int& x, int& y);
  void MoveCursor(int x, int y);
  void SetCursor(int x, int y);
}  // namespace tui

#endif /* ifndef TUI_TERMINAL_CURSOR_HPP */
