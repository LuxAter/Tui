#include "output/buffer.hpp"

#include <stdio.h>

#include <iostream>

#include "output/attr.hpp"

tui::Buffer::Char::Char() { ch = unsigned(); }
tui::Buffer::Char::Char(unsigned int _ch) : ch(_ch) {}
tui::Buffer::Char::Char(char _ch) { ch = static_cast<unsigned int>(_ch); }
tui::Buffer::Char::Char(wchar_t _ch) { ch = static_cast<unsigned int>(_ch); }

bool tui::Buffer::Char::operator==(const Char& rhs) {
  return (ch == rhs.ch && attrs == rhs.attrs);
}
bool tui::Buffer::Char::operator!=(const Char& rhs) { return !(*this == rhs); }

tui::Buffer::Buffer() {}

tui::Buffer::Buffer(unsigned int w, unsigned int h) {
  size[0] = w;
  size[1] = h;
  display_buffer =
      std::vector<std::vector<Char>>(h, std::vector<Char>(w, Char()));
  write_buffer = display_buffer;
  sub_buffer = display_buffer;
}

void tui::Buffer::Clear() {
  write_buffer = std::vector<std::vector<Char>>(
      size[1], std::vector<Char>(size[0], Char()));
  sub_buffer = write_buffer;
}

void tui::Buffer::Swap() {
  Char null;
  for (unsigned int i = 0; i < size[1]; i++) {
    for (unsigned int j = 0; j < size[0]; j++) {
      if (display_buffer[i][j] != write_buffer[i][j] ||
          sub_buffer[i][j] != null) {
        if (sub_buffer[i][j] != null) {
          display_buffer[i][j] = sub_buffer[i][j];
        } else {
          display_buffer[i][j] = write_buffer[i][j];
        }
        WriteChar(display_buffer[i][j], i, j);
      }
      // if (display_buffer[i][j] != write_buffer[i][j] ||
      // sub_buffer[i][j] != Char()) {
      // display_buffer[i][j] = write_buffer[i][j];
      // if (sub_buffer[i][j] != Char()) {
      // display_buffer[i][j] = sub_buffer[i][j];
      // }
      // WriteChar(display_buffer[i][j], i, j);
      // }
    }
  }
  if (display_ == true) {
    fflush(stdout);
  }
}

void tui::Buffer::Refresh() { Swap(); }

void tui::Buffer::SetDisplayBuffer(bool setting) { display_ = setting; }

void tui::Buffer::OffSet(unsigned int x, unsigned int y) { offset = {{x, y}}; }

void tui::Buffer::SetTarget(tui::Buffer* _target) { target = _target; }

void tui::Buffer::Write(unsigned int& x, unsigned int& y, std::string str) {
  unsigned int head[2] = {x, y};
  for (unsigned int i = 0; i < str.size(); i++) {
    if (str[i] == '\n') {
      head[1]++;
      head[0] = 0;
    } else {
      write_buffer[head[0]][head[1]] = str[i];
      write_buffer[head[0]][head[1]].attrs = tui::_active_attrs;
      write_buffer[head[0]][head[1]].attrs.push_back(tui::_active_color);
      write_buffer[head[0]][head[1]].attrs.push_back(
          tui::_active_background_color);
      head[0]++;
    }
    if (head[0] >= write_buffer.size()) {
      head[0] = 0;
      head[1]++;
    }
    if (head[1] >= write_buffer[0].size()) {
      RollBuffer();
      head[1]--;
      head[0] = 0;
    }
  }
  x = head[0];
  y = head[1];
}

void tui::Buffer::Write(unsigned int x, unsigned int y, Char ch) {
  // if (x >= write_buffer.size()) {
  // x = 0;
  // y++;
  // }
  // if (y >= write_buffer[0].size()) {
  // RollBuffer();
  // y--;
  // x = 0;
  // }
  write_buffer[x][y] = ch;
}

void tui::Buffer::WriteSub(unsigned int& x, unsigned int& y, std::string str) {
  unsigned int head[2] = {x, y};
  for (unsigned int i = 0; i < str.size(); i++) {
    if (str[i] == '\n') {
      head[1]++;
      head[0] = 0;
    } else {
      sub_buffer[head[0]][head[1]] = str[i];
      sub_buffer[head[0]][head[1]].attrs = tui::_active_attrs;
      sub_buffer[head[0]][head[1]].attrs.push_back(tui::_active_color);
      sub_buffer[head[0]][head[1]].attrs.push_back(
          tui::_active_background_color);
      head[0]++;
    }
    if (head[0] >= sub_buffer.size()) {
      head[0] = 0;
      head[1]++;
    }
    if (head[1] >= sub_buffer[0].size()) {
      RollBuffer();
      head[1]--;
      head[0] = 0;
    }
  }
  x = head[0];
  y = head[1];
}

void tui::Buffer::WriteSub(unsigned int x, unsigned int y, Char ch) {
  // if (x >= write_buffer.size()) {
  // x = 0;
  // y++;
  // }
  // if (y >= write_buffer[0].size()) {
  // RollBuffer();
  // y--;
  // x = 0;
  // }
  sub_buffer[x][y] = ch;
}

void tui::Buffer::Fill(Char ch) {
  for (unsigned int i = 0; i < size[1]; i++) {
    for (unsigned int j = 0; j < size[0]; j++) {
      write_buffer[i][j] = ch;
    }
  }
}

void tui::Buffer::FillLine(unsigned int a_x, unsigned int a_y, unsigned int b_x,
                           unsigned int b_y, Char ch) {
  if (a_x == b_x) {
    unsigned int tmp_max = std::max(a_y, b_y);
    unsigned int tmp_min = std::min(a_y, b_y);
    a_y = tmp_min;
    b_y = tmp_max;
    for (unsigned int i = a_y; i < b_y; i++) {
      write_buffer[a_x][i] = ch;
    }
  }
}

void tui::Buffer::WriteChar(Char ch, int x, int y) {
  if (display_ == true) {
    if (ch.ch != 0) {
      for (std::size_t i = 0; i < ch.attrs.size(); i++) {
        printf("%s", ch.attrs[i].c_str());
      }
      printf("\033[%i;%iH%c\033[0m", y + 1 + offset[1], x + 1 + offset[0],
             ch.ch);
    } else {
      printf("\033[%i;%iH \033[0m", y + 1 + offset[1], x + 1 + offset[0]);
    }
  } else if (target != nullptr) {
    target->WriteSub(x + offset[0], y + offset[1], ch);
  }
}

void tui::Buffer::RollBuffer() {
  for (unsigned int i = 0; i < write_buffer.size(); i++) {
    for (unsigned int j = 1; j < write_buffer[i].size(); j++) {
      write_buffer[i][j - 1] = write_buffer[i][j];
      if (j == write_buffer[i].size() - 1) {
        write_buffer[i][j] = Char();
      }
    }
  }
}
