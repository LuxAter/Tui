#include "window/canvas.hpp"

#include <array>
#include <bitset>
#include <map>
#include <string>
#include <vector>

#include "window/window.hpp"

#include <iomanip>
#include <iostream>

tui::Canvas::Canvas() { ResizeGrid(); }

tui::Canvas::Canvas(int w, int h) {
  window_pos_ = {{0, 0, w, h}};
  window_buffer_ = tui::Buffer(w, h);
  ResizeGrid();
}

tui::Canvas::Canvas(int x, int y, int w, int h) {
  window_pos_ = {{x, y, w, h}};
  window_buffer_ = tui::Buffer(w, h);
  window_buffer_.OffSet(x, y);
  ResizeGrid();
}

tui::Canvas::Canvas(const Canvas& rhs) {}

void tui::Canvas::SetPixel(PixelFormat format) {
  pixel_format_ = format;
  ResizeGrid();
}

void tui::Canvas::SetOrigin(int x, int y) { origin_ = {{x, y}}; }

void tui::Canvas::SetOrigin(double x, double y) {
  origin_ = {{static_cast<int>(x * size_[0]), static_cast<int>(y * size_[1])}};
}

void tui::Canvas::DrawPoint(int x, int y) {
  if (static_cast<unsigned int>(x + origin_[0]) < pixel_data.size() &&
      static_cast<unsigned int>(y + origin_[1]) < pixel_data[0].size()) {
    pixel_data[x + origin_[0]][y + origin_[1]] = true;
  }
  DrawPixels();
}

void tui::Canvas::EnableBorder() {
  border_active_ = true;
  window_buffer_.border_ = true;
  if (cursor[0] == 0) {
    cursor[0]++;
  }
  if (cursor[1] == 0) {
    cursor[1]++;
  }
  ResizeGrid();
}

void tui::Canvas::DisableBorder() {
  border_active_ = false;
  window_buffer_.border_ = false;
  ResizeGrid();
}

int tui::Canvas::MaxX() { return (pixel_data.size() - origin_[0]); }

int tui::Canvas::MinX() { return -origin_[0]; }

int tui::Canvas::MaxY() { return (pixel_data[0].size() - origin_[1]); }

int tui::Canvas::MinY() { return -origin_[1]; }

void tui::Canvas::ResizeGrid() {
  double x_char = 0, y_char = 0;
  double origin_x = origin_[0] / size_[0];
  double origin_y = origin_[1] / size_[1];
  if (pixel_format_ == TWO_BLOCK) {
    x_char = 0.5;
    y_char = 1;
  } else if (pixel_format_ == BLOCK) {
    x_char = 1;
    y_char = 1;
  } else if (pixel_format_ == VERTICAL_BLOCK) {
    x_char = 2;
    y_char = 1;
  } else if (pixel_format_ == HORIZONTAL_BLOCK) {
    x_char = 1;
    y_char = 2;
  } else if (pixel_format_ == QUARTER_BLOCK) {
    x_char = 2;
    y_char = 2;
  } else if (pixel_format_ == BRAILLE) {
    x_char = 2;
    y_char = 4;
  }
  size_ = {{static_cast<unsigned int>((window_pos_[2] - 2 * border_active_) *
                                      x_char),
            static_cast<unsigned int>((window_pos_[3] - 2 * border_active_) *
                                      y_char)}};

  pixel_data.resize(size_[0]);
  for (unsigned int i = 0; i < pixel_data.size(); i++) {
    pixel_data[i].resize(size_[1]);
  }
  origin_ = {{static_cast<int>(origin_x * size_[0]),
              static_cast<int>(origin_y * size_[1])}};
  // Print("%ix%i\n", window_pos_[2], window_pos_[3]);
  Print("%ix%i\n", size_[0], size_[1]);
}

void tui::Canvas::DrawPixels() {
  if (pixel_format_ == BLOCK) {
    for (unsigned int i = 0; i < pixel_data.size(); i++) {
      for (unsigned int j = 0; j < pixel_data[i].size(); j++) {
        if (pixel_data[i][j] == true) {
          mvPrint(i + border_active_, window_pos_[3] - j - 2 * border_active_,
                  9608);
        }
      }
    }
  } else if (pixel_format_ == TWO_BLOCK) {
    for (unsigned int i = 0; i < pixel_data.size(); i++) {
      for (unsigned int j = 0; j < pixel_data[i].size(); j++) {
        if (pixel_data[i][j] == true) {
          mvPrint((2 * i) + border_active_,
                  window_pos_[3] - j - 2 * border_active_, 9608);
          mvPrint((2 * i) + border_active_ + 1,
                  window_pos_[3] - j - 2 * border_active_, 9608);
        }
      }
    }
  } else if (pixel_format_ == VERTICAL_BLOCK) {
    for (unsigned int i = 0; i < pixel_data.size(); i += 2) {
      for (unsigned int j = 0; j < pixel_data[i].size(); j++) {
        unsigned int ch = 0;
        if (pixel_data[i][j] == true) {
          ch = 9612;
        }
        if (pixel_data[i + 1][j] == true) {
          if (ch == 0) {
            ch = 9616;
          } else {
            ch = 9608;
          }
        }
        if (ch != 0) {
          mvPrint((i / 2) + border_active_ + 1,
                  window_pos_[3] - j - 2 * border_active_, ch);
        }
      }
    }
  } else if (pixel_format_ == HORIZONTAL_BLOCK) {
    for (unsigned int i = 0; i < pixel_data.size(); i++) {
      for (unsigned int j = 0; j < pixel_data[i].size(); j += 2) {
        unsigned int ch = 0;
        if (pixel_data[i][j] == true) {
          ch = 9604;
        }
        if (pixel_data[i][j + 1] == true) {
          if (ch == 0) {
            ch = 9600;
          } else {
            ch = 9608;
          }
        }
        if (ch != 0) {
          mvPrint(i + border_active_ + 1,
                  window_pos_[3] - (j / 2) - 2 * border_active_, ch);
        }
      }
    }
  } else if (pixel_format_ == QUARTER_BLOCK) {
    for (unsigned int i = 0; i < pixel_data.size(); i += 2) {
      for (unsigned int j = 0; j < pixel_data[i].size(); j += 2) {
        std::bitset<4> ch;
        if (pixel_data[i][j + 1] == true) {
          ch.set(0);
        }
        if (pixel_data[i + 1][j + 1] == true) {
          ch.set(1);
        }
        if (pixel_data[i][j] == true) {
          ch.set(2);
        }
        if (pixel_data[i + 1][j] == true) {
          ch.set(3);
        }
        unsigned int c = GetChar(ch);
        if (ch != 0) {
          mvPrint((i / 2) + border_active_ + 1,
                  window_pos_[3] - (j / 2) - 2 * border_active_, c);
        }
      }
    }
  } else if (pixel_format_ == BRAILLE) {
    for (unsigned int i = 0; i < pixel_data.size() - 2; i += 2) {
      for (unsigned int j = 0; j < pixel_data[i].size() - 4; j += 4) {
        std::bitset<8> ch;
        if (pixel_data[i][j + 3] == true) {
          ch.set(0);
        }
        if (pixel_data[i][j + 2] == true) {
          ch.set(1);
        }
        if (pixel_data[i][j + 1] == true) {
          ch.set(2);
        }
        if (pixel_data[i + 1][j + 3] == true) {
          ch.set(3);
        }
        if (pixel_data[i + 1][j + 2] == true) {
          ch.set(4);
        }
        if (pixel_data[i + 1][j + 1] == true) {
          ch.set(5);
        }
        if (pixel_data[i][j] == true) {
          ch.set(6);
        }
        if (pixel_data[i + 1][j] == true) {
          ch.set(7);
        }
        unsigned int c = GetChar(ch);
        if (ch != 0) {
          mvPrint((i / 2) + border_active_ + 1,
                  window_pos_[3] - (j / 4) - 2 * border_active_, c);
        }
      }
    }
  }
}

unsigned int tui::Canvas::GetChar(std::bitset<4> bits) {
  std::string bit_str = bits.to_string<char, std::string::traits_type,
                                       std::string::allocator_type>();
  std::map<std::string, unsigned int> char_map = {
      {"0000", 0},    {"0001", 9624}, {"0010", 9629}, {"0100", 9622},
      {"1000", 9623}, {"1100", 9604}, {"1010", 9616}, {"1001", 9626},
      {"0110", 9630}, {"0101", 9612}, {"0011", 9600}, {"1110", 9631},
      {"1101", 9625}, {"0111", 9672}, {"1011", 9628}, {"1111", 9608}};
  return char_map[bit_str];
}

unsigned int tui::Canvas::GetChar(std::bitset<8> bits) {
  unsigned int braille = 0;
  unsigned int tens = 0;
  if (bits.test(0)) {
    braille += 1;
  }
  if (bits.test(1)) {
    braille += 2;
  }
  if (bits.test(2)) {
    braille += 4;
  }
  if (bits.test(3)) {
    braille += 8;
  }
  if (bits.test(4)) {
    braille += 0;
    tens += 1;
  }
  if (bits.test(5)) {
    braille += 0;
    tens += 2;
  }
  if (bits.test(6)) {
    braille += 0;
    tens += 4;
  }
  if (bits.test(7)) {
    braille += 0;
    tens += 8;
  }
  if (braille != 0) {
    std::cout << bits;
    std::cout << "> " << std::setw(3) << std::setfill(' ') << braille << "->";
    braille = 10240 + std::stoi(std::to_string(braille), nullptr, 16);
    std::cout << std::setw(5) << braille << "\n";
  }
  return braille;
}
