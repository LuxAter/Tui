#ifndef TUI_OUTPUT_BUFFER_HPP
#define TUI_OUTPUT_BUFFER_HPP

#include <vector>

namespace tui {
  static std::vector<std::vector<unsigned int>> display_buffer_, write_buffer_;
  // static unsigned int display_buffer_[][];
  // static unsigned int write_buffer_[][];

  void SwapBuffers();
  void Refresh();
  void Write(unsigned int x, unsigned int y, const char* str, int length);

}  // namespace tui

#endif /* ifndef TUI_OUTPUT_BUFFER_HPP */
