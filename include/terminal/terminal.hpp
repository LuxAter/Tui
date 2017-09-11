#ifndef TUI_TERMINAL_TERMINAL_HPP
#define TUI_TERMINAL_TERMINAL_HPP

#include <termios.h>

namespace tui {
  static struct termios base_term_;
  static bool echo_ = true, cursor_ = true, raw_ = false;

  void SaveTerm();
  void RestoreTerm();

  void Echo();
  void NoEcho();

  void Cursor();
  void NoCursor();

  void Raw();
  void NoRaw();
}  // namespace tui

#endif /* ifndef TUI_TERMINAL_TERMINAL_HPP */
