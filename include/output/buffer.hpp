#ifndef TUI_OUTPUT_BUFFER_HPP
#define TUI_OUTPUT_BUFFER_HPP

#include <array>
#include <string>
#include <vector>

namespace tui {
  class Buffer {
   public:
    class Char {
     public:
      Char();
      Char(unsigned int _ch);
      Char(char _ch);
      Char(wchar_t _ch);
      unsigned int ch;
      std::vector<std::string> attrs;
      bool operator==(const Char& rhs);
      bool operator!=(const Char& rhs);
      std::ostream& operator<<(std::ostream& out);
    };
    Buffer();
    Buffer(unsigned int w, unsigned int h);
    void Clear();
    void Swap();
    void Refresh();

    void SetDisplayBuffer(bool setting);
    void OffSet(unsigned int x, unsigned int y);
    void SetTarget(tui::Buffer* _target);

    void Write(unsigned int& x, unsigned int& y, std::string str,
               std::vector<std::string> attrs, std::string color,
               std::string background_color);
    void Write(unsigned int x, unsigned int y, Char ch);
    void WriteSub(unsigned int x, unsigned int y, Char ch);

    void Fill(Char ch);
    void FillLine(unsigned int a_x, unsigned int a_y, unsigned int b_x,
                  unsigned int b_y, Char ch);

   private:
    void WriteChar(Char ch, int x, int y);
    void RollBuffer();
    std::string GetChar(unsigned int ch);

    tui::Buffer* target = nullptr;
    std::vector<std::vector<Char>> display_buffer, write_buffer, sub_buffer;
    std::array<unsigned int, 2> size = {{0, 0}};
    std::array<unsigned int, 2> offset = {{0, 0}};
    bool display_ = false;
  };

}  // namespace tui

#endif /* ifndef TUI_OUTPUT_BUFFER_HPP */
