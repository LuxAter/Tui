#include "window/window.hpp"

#include <stdarg.h>
#include <wchar.h>
#include <iostream>
#include <string>
#include <vector>

#include "init.hpp"
#include "output/buffer.hpp"
#include "window/canvas.hpp"

tui::Window::Window() {}

tui::Window::Window(int w, int h) {
  window_pos_ = {{0, 0, w, h}};
  window_buffer_ = tui::Buffer(w, h);
}

tui::Window::Window(int x, int y, int w, int h) {
  window_pos_ = {{x, y, w, h}};
  window_buffer_ = tui::Buffer(w, h);
  window_buffer_.OffSet(x, y);
}

tui::Window::~Window() {}

void tui::Window::Show() { window_buffer_.Refresh(); }

void tui::Window::Refresh() { Show(); }

void tui::Window::Resize(int w, int h) {}

void tui::Window::Position(int x, int y) {}

void tui::Window::Clear() { window_buffer_.Clear(); }

void tui::Window::Print(std::wstring str, ...) {
  va_list args;
  va_start(args, str);
  Print(str, args);
  va_end(args);
}

void tui::Window::mvPrint(unsigned x, unsigned y, std::wstring str, ...) {
  va_list args;
  va_start(args, str);
  mvPrint(x, y, str, args);
  va_end(args);
}
void tui::Window::Print(std::wstring str, va_list args) {
  wchar_t buffer[255];
  vswprintf(buffer, sizeof(buffer), str.c_str(), args);
  window_buffer_.Write(cursor[0], cursor[1], std::wstring(buffer),
                       active_attrs_, active_color_, active_background_color_);
}

void tui::Window::mvPrint(unsigned x, unsigned y, std::wstring str,
                          va_list args) {
  wchar_t buffer[255];
  vswprintf(buffer, sizeof(buffer), str.c_str(), args);
  cursor = {{x, y}};
  window_buffer_.Write(cursor[0], cursor[1], std::wstring(buffer),
                       active_attrs_, active_color_, active_background_color_);
}

void tui::Window::Print(std::string str, ...) {
  va_list args;
  va_start(args, str);
  Print(GetWString(str), args);
  va_end(args);
}

void tui::Window::mvPrint(unsigned x, unsigned y, std::string str, ...) {
  va_list args;
  va_start(args, str);
  mvPrint(x, y, str, args);
  va_end(args);
}
void tui::Window::Print(std::string str, va_list args) {
  wchar_t buffer[255];
  vswprintf(buffer, sizeof(buffer), GetWString(str).c_str(), args);
  window_buffer_.Write(cursor[0], cursor[1], std::wstring(buffer),
                       active_attrs_, active_color_, active_background_color_);
}

void tui::Window::mvPrint(unsigned x, unsigned y, std::string str,
                          va_list args) {
  wchar_t buffer[255];
  vswprintf(buffer, sizeof(buffer), GetWString(str).c_str(), args);
  cursor = {{x, y}};
  window_buffer_.Write(cursor[0], cursor[1], std::wstring(buffer),
                       active_attrs_, active_color_, active_background_color_);
}

void tui::Window::Print(unsigned int ch) {
  window_buffer_.Write(cursor[0], cursor[1], ch, active_attrs_, active_color_,
                       active_background_color_);
}
void tui::Window::mvPrint(unsigned int x, unsigned int y, unsigned int ch) {
  cursor = {{x, y}};
  window_buffer_.Write(cursor[0], cursor[1], ch, active_attrs_, active_color_,
                       active_background_color_);
}

void tui::Window::MoveCursor(unsigned x, unsigned y) {
  cursor[0] = x;
  cursor[1] = y;
}

void tui::Window::Fill(unsigned int ch) {
  Buffer::Char c(ch);
  c.attrs = active_attrs_;
  c.attrs.push_back(active_color_);
  c.attrs.push_back(active_background_color_);
  window_buffer_.Fill(c);
}

void tui::Window::Line(unsigned int x0, unsigned int y0, unsigned int x1,
                       unsigned int y1, unsigned int ch) {
  Buffer::Char c(ch);
  c.attrs = active_attrs_;
  c.attrs.push_back(active_color_);
  c.attrs.push_back(active_background_color_);
  window_buffer_.FillLine(x0, y0, x1, y1, c);
}

void tui::Window::Box() { Box(9487, 9473, 9491, 9475, 9475, 9495, 9473, 9499); }
void tui::Window::Box(unsigned c, unsigned v, unsigned h) {
  Box(c, h, c, v, v, c, h, c);
}
void tui::Window::Box(unsigned int ul, unsigned int u, unsigned int ur,
                      unsigned int l, unsigned int r, unsigned int bl,
                      unsigned int b, unsigned int br) {
  Buffer::Char c;
  c.attrs = active_attrs_;
  c.attrs.push_back(active_color_);
  c.attrs.push_back(active_background_color_);
  c.ch = ul;
  window_buffer_.Write(0, 0, c);
  c.ch = ur;
  window_buffer_.Write(window_pos_[2] - 1, 0, c);
  c.ch = bl;
  window_buffer_.Write(0, window_pos_[3] - 1, c);
  c.ch = br;
  window_buffer_.Write(window_pos_[2] - 1, window_pos_[3] - 1, c);
  c.ch = u;
  window_buffer_.FillLine(1, 0, window_pos_[2] - 2, 0, c);
  c.ch = l;
  window_buffer_.FillLine(0, 1, 0, window_pos_[3] - 2, c);
  c.ch = r;
  window_buffer_.FillLine(window_pos_[2] - 1, 1, window_pos_[2] - 1,
                          window_pos_[3] - 2, c);
  c.ch = b;
  window_buffer_.FillLine(1, window_pos_[3] - 1, window_pos_[2] - 2,
                          window_pos_[3] - 1, c);
}

void tui::Window::EnableBorder() {
  border_active_ = true;
  window_buffer_.border_ = true;
  if (cursor[0] == 0) {
    cursor[0]++;
  }
  if (cursor[1] == 0) {
    cursor[1]++;
  }
}

void tui::Window::DisableBorder() {
  window_buffer_.border_ = false;
  border_active_ = false;
}

void tui::Window::EnableScroll() { window_buffer_.scroll_ = true; }
void tui::Window::DisableScroll() { window_buffer_.scroll_ = false; }

void tui::Window::AttrOn(Attr attr) {
  if (attr == NONE) {
    active_attrs_.clear();
  }
  unsigned int attr_int = static_cast<unsigned int>(attr);
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "\033[%im", attr_int);
  active_attrs_.push_back(std::string(buffer));
}

void tui::Window::AttrOff(Attr attr) {
  unsigned int attr_int = static_cast<unsigned int>(attr);
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "\033[%im", attr_int);
  std::string match(buffer);
  for (unsigned int i = 0; i < active_attrs_.size(); i++) {
    if (active_attrs_[i] == match) {
      active_attrs_.erase(active_attrs_.begin() + i);
      break;
    }
  }
}

void tui::Window::SetColor(ColorPair color) {
  SetColor(color.fg);
  SetBackground(color.bg);
}
void tui::Window::SetColor(ColorValue color) {
  if (color.id == 1) {
    SetColor(color.id_enum);
  } else if (color.id == 2) {
    SetColor(color.id_ch);
  } else if (color.id == 3) {
    SetColor(color.id_r, color.id_g, color.id_b);
  }
}
void tui::Window::SetColor(Color color) {
  if (_color_access == COLOR_16 || _color_access == COLOR_256 ||
      _color_access == TRUE_COLOR) {
    if (color == DEFAULT) {
      active_color_ = "\033[39m";
    } else {
      unsigned int color_int = static_cast<unsigned int>(color);
      if (color_int > 8) {
        color_int += 52;
      }
      color_int += 29;
      char buffer[50];
      snprintf(buffer, sizeof(buffer), "\033[%im", color_int);
      active_color_ = std::string(buffer);
    }
  } else {
    std::cerr << "Current terminal does not support colors\n";
  }
}
void tui::Window::SetColor(unsigned char color) {
  if (_color_access == COLOR_256 || _color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[38;5;%im", color);
    active_color_ = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support 256 colors\n";
  }
}
void tui::Window::SetColor(unsigned char r, unsigned char g, unsigned char b) {
  if (_color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[38;2;%i;%i;%im", r, g, b);
    active_color_ = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support true colors\n";
  }
}

void tui::Window::SetBackground(ColorValue color) {
  if (color.id == 1) {
    SetBackground(color.id_enum);
  } else if (color.id == 2) {
    SetBackground(color.id_ch);
  } else if (color.id == 3) {
    SetBackground(color.id_r, color.id_g, color.id_b);
  }
}
void tui::Window::SetBackground(Color color) {
  if (_color_access == COLOR_16 || _color_access == COLOR_256 ||
      _color_access == TRUE_COLOR) {
    if (color == DEFAULT) {
      active_background_color_ = "\033[49m";
    } else {
      unsigned int color_int = static_cast<unsigned int>(color);
      if (color_int > 8) {
        color_int += 52;
      }
      color_int += 39;
      char buffer[50];
      snprintf(buffer, sizeof(buffer), "\033[%im", color_int);
      active_background_color_ = std::string(buffer);
    }
  } else {
    std::cerr << "Current terminal does not support colors\n";
  }
}
void tui::Window::SetBackground(unsigned char color) {
  if (_color_access == COLOR_256 || _color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[48;5;%im", color);
    active_background_color_ = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support 256 colors\n";
  }
}
void tui::Window::SetBackground(unsigned char r, unsigned char g,
                                unsigned char b) {
  if (_color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[48;2;%i;%i;%im", r, g, b);
    active_background_color_ = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support true colors\n";
  }
}

tui::Buffer* tui::Window::GetBufferPointer() { return &window_buffer_; }

tui::Window tui::Window::CreateWindow() {
  Window sub(window_pos_[0], window_pos_[1], window_pos_[2], window_pos_[3]);
  sub.GetBufferPointer()->SetTarget(&window_buffer_);
  return sub;
}

tui::Window tui::Window::CreateWindow(int w, int h) {
  Window sub(w, h);
  sub.GetBufferPointer()->SetTarget(&window_buffer_);
  return sub;
}

tui::Window tui::Window::CreateWindow(int x, int y, int w, int h) {
  Window sub(x, y, w, h);
  sub.GetBufferPointer()->SetTarget(&window_buffer_);
  return sub;
}

tui::Canvas tui::Window::CreateCanvas() {
  Canvas sub(window_pos_[0], window_pos_[1], window_pos_[2], window_pos_[3]);
  sub.GetBufferPointer()->SetTarget(&window_buffer_);
  return sub;
}

tui::Canvas tui::Window::CreateCanvas(int w, int h) {
  Canvas sub(w, h);
  sub.GetBufferPointer()->SetTarget(&window_buffer_);
  return sub;
}

tui::Canvas tui::Window::CreateCanvas(int x, int y, int w, int h) {
  Canvas sub(x, y, w, h);
  sub.GetBufferPointer()->SetTarget(&window_buffer_);
  return sub;
}
