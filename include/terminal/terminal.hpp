#ifndef TUI_TERMINAL_TERMINAL_HPP
#define TUI_TERMINAL_TERMINAL_HPP

#include <termios.h>

namespace tui {

  void SaveTerm();
  void RestoreTerm();

  void Echo();
  void NoEcho();

  void Cursor();
  void NoCursor();

  void Raw();
  void NoRaw();

  void Clear();
  void ClearLine();
}  // namespace tui

#endif /* ifndef TUI_TERMINAL_TERMINAL_HPP */
