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

std::ostream& tui::Buffer::Char::operator<<(std::ostream& out) {
  out << static_cast<char>(ch);
  return out;
}

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
      if ((write_buffer[i][j] != null &&
           display_buffer[i][j] != write_buffer[i][j]) ||
          (sub_buffer[i][j] != null &&
           display_buffer[i][j] != sub_buffer[i][j])) {
        if (sub_buffer[i][j] != null) {
          display_buffer[i][j] = sub_buffer[i][j];
        } else {
          display_buffer[i][j] = write_buffer[i][j];
        }
        WriteChar(display_buffer[i][j], i, j);
      }
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

void tui::Buffer::Write(unsigned int& x, unsigned int& y, std::string str,
                        std::vector<std::string> attrs, std::string color,
                        std::string background_color) {
  unsigned int head[2] = {x, y};
  for (unsigned int i = 0; i < str.size(); i++) {
    if (str[i] == '\n') {
      head[1]++;
      head[0] = 0;
    } else {
      write_buffer[head[0]][head[1]] = str[i];
      write_buffer[head[0]][head[1]].attrs = attrs;
      write_buffer[head[0]][head[1]].attrs.push_back(color);
      write_buffer[head[0]][head[1]].attrs.push_back(background_color);
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
  write_buffer[x][y] = ch;
}

void tui::Buffer::WriteSub(unsigned int x, unsigned int y, Char ch) {
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
    for (unsigned int i = a_y; i <= b_y; i++) {
      write_buffer[a_x][i] = ch;
    }
  } else {
    if (b_x < a_x) {
      unsigned int tmp = a_x;
      a_x = b_x;
      b_x = tmp;
      tmp = a_y;
      a_y = b_y;
      b_y = tmp;
    }
    double m = static_cast<double>(static_cast<signed int>(b_y) -
                                   static_cast<signed int>(a_y)) /
               static_cast<double>(static_cast<signed int>(b_x) -
                                   static_cast<signed int>(a_x));
    unsigned int t = a_x;
    while (t <= b_x) {
      unsigned int y =
          static_cast<unsigned int>(m * (t - static_cast<signed int>(a_x)) +
                                    static_cast<signed int>(a_y));
      Write(t, y, ch);
      t++;
    }
  }
}

void tui::Buffer::WriteChar(Char ch, int x, int y) {
  if (display_ == true) {
    if (ch.ch != 0) {
      std::string str = GetChar(ch.ch);
      for (std::size_t i = 0; i < ch.attrs.size(); i++) {
        printf("%s", ch.attrs[i].c_str());
      }
      printf("\033[%i;%iH%s\033[0m", y + 1 + offset[1], x + 1 + offset[0],
             str.c_str());
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

std::string tui::Buffer::GetChar(unsigned int ch) {
  std::string out;

  if (ch <= 0x7f)
    out.append(1, static_cast<char>(ch));
  else if (ch <= 0x7ff) {
    out.append(1, static_cast<char>(0xc0 | ((ch >> 6) & 0x1f)));
    out.append(1, static_cast<char>(0x80 | (ch & 0x3f)));
  } else if (ch <= 0xffff) {
    out.append(1, static_cast<char>(0xe0 | ((ch >> 12) & 0x0f)));
    out.append(1, static_cast<char>(0x80 | ((ch >> 6) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | (ch & 0x3f)));
  } else {
    out.append(1, static_cast<char>(0xf0 | ((ch >> 18) & 0x07)));
    out.append(1, static_cast<char>(0x80 | ((ch >> 12) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | ((ch >> 6) & 0x3f)));
    out.append(1, static_cast<char>(0x80 | (ch & 0x3f)));
  }
  return out;
}
