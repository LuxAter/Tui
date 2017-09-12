#ifndef TUI_INPUT_INPUT_HPP
#define TUI_INPUT_INPUT_HPP

namespace tui {

  extern int timeout_;

  unsigned int getch();
  bool kbhit(int timeout_ms = timeout_);
  unsigned int GetKeyCode(char key);
  unsigned int GetEscapeKey(char key);

  void SetTimeout(int timeout);
}  // namespace tui

#endif /* ifndef TUI_INPUT_INPUT_HPP */
