#include "window/window.hpp"

#include <stdarg.h>
#include <string>
#include <vector>

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

void tui::Window::Clear() { window_buffer_.Clear(); }

void tui::Window::Print(std::string str, ...) {
  va_list args;
  va_start(args, str);
  Print(str, args);
  va_end(args);
}

void tui::Window::mvPrint(unsigned x, unsigned y, std::string str, ...) {
  va_list args;
  va_start(args, str);
  mvPrint(x, y, str, args);
  va_end(args);
}
void tui::Window::Print(std::string str, va_list args) {
  char buffer[255];
  vsnprintf(buffer, sizeof(buffer), str.c_str(), args);
  window_buffer_.Write(cursor[0], cursor[1], std::string(buffer));
}

void tui::Window::mvPrint(unsigned x, unsigned y, std::string str,
                          va_list args) {
  char buffer[255];
  vsnprintf(buffer, sizeof(buffer), str.c_str(), args);
  cursor = {{x, y}};
  window_buffer_.Write(cursor[0], cursor[1], std::string(buffer));
}

void tui::Window::Fill(char ch) { window_buffer_.Fill(ch); }

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
