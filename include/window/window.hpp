#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

#include <array>
#include <string>

#include "../output/buffer.hpp"

namespace tui {
  class Window {
   public:
    Window();
    Window(int w, int h);
    Window(int x, int y, int w, int h);
    Window(const Window& copy);
    ~Window();

    void Show();
    void Refresh();

    void Clear();

    void Print(std::string str, ...);
    void mvPrint(unsigned x, unsigned y, std::string str, ...);
    void Print(std::string str, va_list args);
    void mvPrint(unsigned x, unsigned y, std::string str, va_list args);

    void Fill(char ch);

    tui::Buffer* GetBufferPointer();

    tui::Window CreateWindow();
    tui::Window CreateWindow(int w, int h);
    tui::Window CreateWindow(int x, int y, int w, int h);

   private:
    std::array<unsigned, 2> cursor = {{0, 0}};
    unsigned int window_index_;
    std::array<int, 4> window_pos_ = {{0, 0, 0, 0}};
    tui::Buffer window_buffer_;
  };
}  // namespace tui

#endif /* ifndef TUI_WINDOW_HPP */
