#include "output/buffer.hpp"

#include <stdio.h>
#include <sys/ioctl.h>

#include <iostream>

#include "output/attr.hpp"

tui::Char::Char() { ch = unsigned(); }
tui::Char::Char(unsigned int _ch) : ch(_ch) {}
tui::Char::Char(char _ch) { ch = static_cast<unsigned int>(_ch); }
tui::Char::Char(wchar_t _ch) { ch = static_cast<unsigned int>(_ch); }

bool tui::operator==(const Char& lhs, const Char& rhs) {
  return (lhs.ch == rhs.ch && lhs.attrs == rhs.attrs);
}
bool tui::operator!=(const Char& lhs, const Char& rhs) { return !(lhs == rhs); }

void tui::BufferInit() {
  struct winsize size;
  ioctl(0, TIOCGWINSZ, &size);
  int w = size.ws_row, h = size.ws_col;
  display_buffer_ =
      std::vector<std::vector<Char>>(h, std::vector<Char>(w, Char()));
  write_buffer_ = display_buffer_;
}

void tui::BufferClear() {
  struct winsize size;
  ioctl(0, TIOCGWINSZ, &size);
  int w = size.ws_row, h = size.ws_col;
  write_buffer_ =
      std::vector<std::vector<Char>>(h, std::vector<Char>(w, Char()));
}

void tui::RedrawBuffer() {
  int width = display_buffer_.size();
  int height = display_buffer_[0].size();
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (display_buffer_[x][y].ch != 0) {
        for (std::size_t i = 0; i < display_buffer_[x][y].attrs.size(); i++) {
          printf("%s", display_buffer_[x][y].attrs[i].c_str());
        }
        printf("\033[%i;%iH%c\033[0m", y + 1, x + 1, display_buffer_[x][y].ch);
      } else {
        printf("\033[%i;%iH ", y + 1, x + 1);
      }
    }
  }
  fflush(stdout);
}

void tui::SwapBuffers() {
  int width = display_buffer_.size();
  int height = display_buffer_[0].size();
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (display_buffer_[x][y] != write_buffer_[x][y]) {
        display_buffer_[x][y] = write_buffer_[x][y];
        if (display_buffer_[x][y].ch != 0) {
          for (std::size_t i = 0; i < display_buffer_[x][y].attrs.size(); i++) {
            // printf("%i", display_buffer_[x][y].attrs.size());
            printf("%s", display_buffer_[x][y].attrs[i].c_str());
          }
          printf("\033[%i;%iH%c\033[0m", y + 1, x + 1,
                 display_buffer_[x][y].ch);
        } else {
          printf("\033[%i;%iH ", y + 1, x + 1);
        }
      }
    }
  }
  fflush(stdout);
}

void tui::BufferRefresh() { SwapBuffers(); }

void tui::BufferWrite(unsigned int x, unsigned int y, std::string str) {
  unsigned int head[2] = {x, y};
  for (unsigned int i = 0; i < str.size(); i++) {
    write_buffer_[head[0]][head[1]] = str[i];
    write_buffer_[head[0]][head[1]].attrs.push_back(tui::_active_color);
    write_buffer_[head[0]][head[1]].attrs.push_back(
        tui::_active_background_color);
    head[0]++;
    if (head[0] >= write_buffer_.size() - 1) {
      head[0] = 0;
      head[1]++;
    }
  }
}
