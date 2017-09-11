#ifndef TUI_INIT_HPP
#define TUI_INIT_HPP

#include <string>

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
  bool InitTui();
  bool TermTui();
  int HasColor();
}  // namespace tui

#endif /* ifndef TUI_INIT_HPP */
