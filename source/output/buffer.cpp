#include "output/buffer.hpp"

#include <stdio.h>
#include <cmath>
#include <map>

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
      std::vector<std::vector<Char>>(w, std::vector<Char>(h, Char()));
  write_buffer = display_buffer;
  sub_buffer = display_buffer;
}

void tui::Buffer::Clear() {
  write_buffer = std::vector<std::vector<Char>>(
      size[0], std::vector<Char>(size[1], Char()));
  sub_buffer = write_buffer;
}

void tui::Buffer::Swap() {
  Char null;
  if (fast_mode == false) {
    for (unsigned int i = 0; i < size[0]; i++) {
      for (unsigned int j = 0; j < size[1]; j++) {
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
  } else if (fast_mode == true) {
    for (auto& it : updated_data_) {
      if (sub_buffer[it[0]][it[1]] != null) {
        display_buffer[it[0]][it[1]] = sub_buffer[it[0]][it[1]];
      } else {
        display_buffer[it[0]][it[1]] = write_buffer[it[0]][it[1]];
      }
      WriteChar(display_buffer[it[0]][it[1]], it[0], it[1]);
    }
    updated_data_.clear();
  }
  if (display_ == true) {
    fflush(stdout);
  }
}

void tui::Buffer::Refresh() { Swap(); }

void tui::Buffer::SetDisplayBuffer(bool setting) { display_ = setting; }

void tui::Buffer::SetFastMode(bool setting) {fast_mode = setting;}

void tui::Buffer::OffSet(unsigned int x, unsigned int y) { offset = {{x, y}}; }

void tui::Buffer::SetTarget(tui::Buffer* _target) { target = _target; }

void tui::Buffer::Write(unsigned int& x, unsigned int& y, std::wstring str,
                        std::vector<std::string> attrs, std::string color,
                        std::string background_color) {
  unsigned int head[2] = {x, y};
  if (head[0] >= write_buffer.size() - border_) {
    head[0] = border_;
    head[1]++;
  }
  if (head[1] >= write_buffer[0].size() - border_) {
    RollBuffer();
    head[1]--;
    head[0] = border_;
  }
  for (unsigned int i = 0; i < str.size(); i++) {
    if (int(str[i]) >= -32 && int(str[i]) <= -17) {
      unsigned val = 0;
      std::map<int, int> bitmap{
          {-32, 0},     {-31, 4096},  {-30, 8192},  {-29, 12288},
          {-28, 16384}, {-27, 20480}, {-26, 24576}, {-25, 28672},
          {-24, 32768}, {-23, 36864}, {-22, 40960}, {-21, 45056},
          {-20, 49152}, {-19, 53248}, {-18, 57344}, {-17, 61440}};
      val = bitmap[int(str[i])];
      double b = 0, c = 0;
      int off = -1 * (((-1 * int(str[i + 1])) % 4) - 4);
      if (off != 0) {
        b = -256.0 * (std::round(((-1 * double(str[i + 1])) + 2.0) / 4.0) - 32);
      } else {
        b = -256.0 * ((-1.0 * (double(str[i + 1]) / 4.0)) - 32.0);
      }
      c = (-1.0 * ((-1.0 * double(str[i + 2])) - 128.0)) + (off * 64.0);
      val += b + c;
      write_buffer[head[0]][head[1]] = val;
      write_buffer[head[0]][head[1]].attrs = attrs;
      write_buffer[head[0]][head[1]].attrs.push_back(color);
      write_buffer[head[0]][head[1]].attrs.push_back(background_color);
      StorePosition(head[0], head[1]);
      head[0]++;
      i += 2;
    } else if (int(str[i]) >= -60 && int(str[i]) <= -32) {
      unsigned val = 0;
      double b = 0, c = 0;
      int off = -1 * (((-1 * int(str[i])) % 4) - 4);
      if (off != 0) {
        b = -256.0 * (std::round(((-1 * double(str[i])) + 2.0) / 4.0) - 16.0);
      } else {
        b = -256.0 * ((-1.0 * (double(str[i]) / 4.0)) - 16.0);
      }
      c = (-1.0 * ((-1.0 * double(str[i + 1])) - 128.0)) + (off * 64.0);
      val += b + c;
      write_buffer[head[0]][head[1]] = val;
      write_buffer[head[0]][head[1]].attrs = attrs;
      write_buffer[head[0]][head[1]].attrs.push_back(color);
      write_buffer[head[0]][head[1]].attrs.push_back(background_color);
      StorePosition(head[0], head[1]);
      head[0]++;
      i += 2;
    } else if (str[i] == '\n') {
      head[1]++;
      head[0] = border_;
    } else {
      write_buffer[head[0]][head[1]] = str[i];
      write_buffer[head[0]][head[1]].attrs = attrs;
      write_buffer[head[0]][head[1]].attrs.push_back(color);
      write_buffer[head[0]][head[1]].attrs.push_back(background_color);
      StorePosition(head[0], head[1]);
      head[0]++;
    }
    if (head[0] >= write_buffer.size() - border_) {
      head[0] = border_;
      head[1]++;
    }
    if (head[1] >= write_buffer[0].size() - border_) {
      RollBuffer();
      head[1]--;
      head[0] = border_;
    }
  }
  x = head[0];
  y = head[1];
}

void tui::Buffer::Write(unsigned int& x, unsigned int& y, unsigned int ch,
                        std::vector<std::string> attrs, std::string color,
                        std::string background_color) {
  unsigned int head[2] = {x, y};
  if (head[0] >= write_buffer.size() - border_) {
    head[0] = border_;
    head[1]++;
  }
  if (head[1] >= write_buffer[0].size() - border_) {
    RollBuffer();
    head[1]--;
    head[0] = border_;
  }
  write_buffer[head[0]][head[1]] = ch;
  write_buffer[head[0]][head[1]].attrs = attrs;
  write_buffer[head[0]][head[1]].attrs.push_back(color);
  write_buffer[head[0]][head[1]].attrs.push_back(background_color);
  StorePosition(head[0], head[1]);
  head[0]++;
  if (head[0] >= write_buffer.size() - border_) {
    head[0] = border_;
    head[1]++;
  }
  if (head[1] >= write_buffer[0].size() - border_) {
    RollBuffer();
    head[1]--;
    head[0] = border_;
  }
  x = head[0], y = head[1];
}

void tui::Buffer::Write(unsigned int x, unsigned int y, Char ch) {
  if (x < write_buffer.size() && y < write_buffer[x].size()) {
    write_buffer[x][y] = ch;
    StorePosition(x, y);
  }
}

void tui::Buffer::WriteSub(unsigned int x, unsigned int y, Char ch) {
  if (x < sub_buffer.size() && y < sub_buffer[x].size()) {
    sub_buffer[x][y] = ch;
    StorePosition(x, y);
  }
}

void tui::Buffer::Fill(Char ch) {
  for (unsigned int i = 0; i < size[0]; i++) {
    for (unsigned int j = 0; j < size[1]; j++) {
      write_buffer[i][j] = ch;
      StorePosition(i, j);
    }
  }
}

void tui::Buffer::FillLine(unsigned int a_x, unsigned int a_y, unsigned int b_x,
                           unsigned int b_y, Char ch) {
  if (a_x < write_buffer.size() && b_x < write_buffer.size() &&
      a_y < write_buffer[a_x].size() && b_y < write_buffer[b_x].size()) {
    if (a_x == b_x) {
      unsigned int tmp_max = std::max(a_y, b_y);
      unsigned int tmp_min = std::min(a_y, b_y);
      a_y = tmp_min;
      b_y = tmp_max;
      for (unsigned int i = a_y; i <= b_y; i++) {
        write_buffer[a_x][i] = ch;
        StorePosition(a_x, i);
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
  if (scroll_ == false) {
    return;
  }
  for (unsigned int i = border_; i < write_buffer.size() - border_; i++) {
    for (unsigned int j = 1 + border_; j < write_buffer[i].size() - border_;
         j++) {
      write_buffer[i][j - 1] = write_buffer[i][j];
      StorePosition(i, j - 1);
      if (j == write_buffer[i].size() - 1 - border_) {
        write_buffer[i][j] = Char(' ');
        StorePosition(i, j);
      }
    }
  }
}

std::string tui::Buffer::GetChar(unsigned int ch) {
  std::string out;

  if (ch <= 0x7f) {
    out.append(1, static_cast<char>(ch));
  } else if (ch <= 0x7ff) {
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

void tui::Buffer::StorePosition(unsigned x, unsigned y) {
  if (fast_mode == true) {
    std::set<std::array<unsigned, 2>>::const_iterator it =
        updated_data_.find(std::array<unsigned, 2>{{x, y}});
    if (it == updated_data_.end()) {
      updated_data_.insert(std::array<unsigned, 2>{{x, y}});
    }
  }
}
