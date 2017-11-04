#ifndef TUI_OUTPUT_BUFFER_HPP
#define TUI_OUTPUT_BUFFER_HPP

#include <string>
#include <vector>

namespace tui {
  struct Char {
    Char();
    Char(unsigned int _ch);
    Char(char _ch);
    Char(wchar_t _ch);
    unsigned int ch;
    std::vector<std::string> attrs;
  };
  bool operator==(const Char& lhs, const Char& rhs);
  bool operator!=(const Char& lhs, const Char& rhs);
  static std::vector<std::vector<Char>> display_buffer_, write_buffer_;

  void BufferInit();
  void BufferClear();
  void RedrawBuffer();
  void SwapBuffers();
  void BufferRefresh();
  void BufferWrite(unsigned int x, unsigned int y, std::string str);

}  // namespace tui

#endif /* ifndef TUI_OUTPUT_BUFFER_HPP */
