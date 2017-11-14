#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

#include <array>
#include <string>

#include "../output/attr.hpp"
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

    void Print(std::wstring str, ...);
    void mvPrint(unsigned x, unsigned y, std::wstring str, ...);
    void Print(std::wstring str, va_list args);
    void mvPrint(unsigned x, unsigned y, std::wstring str, va_list args);
    void Print(std::string str, ...);
    void mvPrint(unsigned x, unsigned y, std::string str, ...);
    void Print(std::string str, va_list args);
    void mvPrint(unsigned x, unsigned y, std::string str, va_list args);
    void Print(unsigned int ch);
    void mvPrint(unsigned int x, unsigned int y, unsigned int ch);

    void Move(unsigned x, unsigned y);

    void Fill(unsigned int ch);
    void Line(unsigned x0, unsigned y0, unsigned x1, unsigned y1,
              unsigned int ch);

    void Box();
    void Box(unsigned c, unsigned v, unsigned h);
    void Box(unsigned int ul, unsigned int u, unsigned int ur, unsigned int l,
             unsigned int r, unsigned int bl, unsigned int b, unsigned int br);
    void EnableBorder();
    void DisableBorder();

    void AttrOn(Attr attr);
    void AttrOff(Attr attr);
    void SetColor(ColorPair color);
    void SetColor(Color color);
    void SetColor(ColorValue color);
    void SetColor(unsigned char color);
    void SetColor(unsigned char r, unsigned char g, unsigned char b);
    void SetBackground(Color color);
    void SetBackground(ColorValue color);
    void SetBackground(unsigned char color);
    void SetBackground(unsigned char r, unsigned char g, unsigned char b);

    tui::Buffer* GetBufferPointer();

    tui::Window CreateWindow();
    tui::Window CreateWindow(int w, int h);
    tui::Window CreateWindow(int x, int y, int w, int h);

   private:
    std::array<unsigned, 2> cursor = {{0, 0}};
    unsigned int window_index_;
    std::array<int, 4> window_pos_ = {{0, 0, 0, 0}};
    tui::Buffer window_buffer_;

    std::vector<std::string> active_attrs_;
    std::string active_color_, active_background_color_;
  };
}  // namespace tui

#endif /* ifndef TUI_WINDOW_HPP */
