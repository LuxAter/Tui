#include "window/canvas.hpp"

#include <math.h>
#include <array>
#include <bitset>
#include <map>
#include <string>
#include <vector>

#include "window/window.hpp"

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
    DrawPixels(x + origin_[0], y + origin_[1]);
  }
}

void tui::Canvas::DrawLine(int ax, int ay, int bx, int by) {
  if (ax == bx && ay == by) {
    ax += origin_[0];
    ay += origin_[1];
    bx += origin_[0];
    by += origin_[1];
    if (ax > 0 && ax < size_[0] && ay > 0 && ay < size_[1]) {
      pixel_data[ax][ay] = true;
      DrawPixels(ax, ay);
    }
    return;
  }
  double m = static_cast<double>(by - ay) / static_cast<double>(bx - ax);
  bool vert = false;
  if (bx - ax == 0) {
    vert = true;
    m = 1;
  }
  ax += origin_[0];
  ay += origin_[1];
  bx += origin_[0];
  by += origin_[1];
  if (vert == true) {
    if (ay > by) {
      std::swap(ay, by);
    }
    for (double y = ay; y < by; y++) {
      if (ax > 0 && ax < size_[0] && y > 0 && y < size_[1]) {
        pixel_data[ax][y] = true;
        DrawPixels(ax, y);
      }
    }
  } else if (std::abs(m) > 1) {
    if (ay > by) {
      std::swap(ay, by);
      std::swap(ax, bx);
    }
    double x = ax;
    for (double y = ay; y <= by; y++) {
      x += (1.0 / m);
      if (x > 0 && x < size_[0] && y > 0 && y < size_[1]) {
        pixel_data[x][y] = true;
        DrawPixels(x, y);
      }
    }
  } else {
    if (ax > bx) {
      std::swap(ax, bx);
      std::swap(ay, by);
    }
    double y = ay;
    for (double x = ax; x <= bx; x++) {
      if (x > 0 && x < size_[0] && y > 0 && y < size_[1]) {
        pixel_data[x][y] = true;
        DrawPixels(x, y);
      }
      y += m;
    }
  }
}

void tui::Canvas::DrawTriangle(int ax, int ay, int bx, int by, int cx, int cy) {
  DrawLine(ax, ay, bx, by);
  DrawLine(bx, by, cx, cy);
  DrawLine(cx, cy, ax, ay);
}

void tui::Canvas::DrawFilledTriangle(int ax, int ay, int bx, int by, int cx,
                                     int cy) {
  DrawFilledPolygon({ax, ay, bx, by, cx, cy});
}

void tui::Canvas::DrawRectangle(int ax, int ay, int bx, int by, int cx, int cy,
                                int dx, int dy) {
  DrawLine(ax, ay, bx, by);
  DrawLine(bx, by, cx, cy);
  DrawLine(cx, cy, dx, dy);
  DrawLine(dx, dy, ax, ay);
}

void tui::Canvas::DrawFilledRectangle(int ax, int ay, int bx, int by, int cx,
                                      int cy, int dx, int dy) {
  DrawFilledPolygon({ax, ay, bx, by, cx, cy, dx, dy});
}

void tui::Canvas::DrawCircle(int c_x, int c_y, int r) {
  c_x += origin_[0];
  c_y += origin_[1];
  int x = r - 1;
  int y = 0;
  int err = (x * x) - (r * r) + r;
  while (x >= y) {
    SetPixel(c_x + x, c_y + y);
    SetPixel(c_x + y, c_y + x);
    SetPixel(c_x - y, c_y + x);
    SetPixel(c_x - x, c_y + y);
    SetPixel(c_x - x, c_y - y);
    SetPixel(c_x - y, c_y - x);
    SetPixel(c_x + y, c_y - x);
    SetPixel(c_x + x, c_y - y);
    if (err <= 0) {
      y++;
      err += 2 * y + 1;
    } else {
      x--;
      err -= x * 2 + 1;
    }
  }
}
void tui::Canvas::DrawFilledCircle(int c_x, int c_y, int r) {
  c_x += origin_[0];
  c_y += origin_[1];
  for (int y = -r; y < r; y++) {
    for (int x = -r; x < r; x++) {
      if (x * x + y * y < r * r) {
        SetPixel(c_x + x, c_y + y);
      }
    }
  }
}

void tui::Canvas::DrawRegularPolygon(int x, int y, int r, int n) {
  std::vector<int> points;
  double delta_theta = (3.1415 * 2) / static_cast<double>(n);
  for (double theta = 1.5708; theta < 7.85; theta += delta_theta) {
    points.push_back(r * std::cos(theta) + x);
    points.push_back(r * std::sin(theta) + y);
  }
  DrawPolygon(points);
}

void tui::Canvas::DrawFilledRegularPolygon(int x, int y, int r, int n) {
  std::vector<int> points;
  double delta_theta = (3.1415 * 2) / static_cast<double>(n);
  for (double theta = 1.5708; theta < 7.85; theta += delta_theta) {
    points.push_back(r * std::cos(theta) + x);
    points.push_back(r * std::sin(theta) + y);
  }
  DrawFilledPolygon(points);
}

void tui::Canvas::DrawPolygon(std::vector<int> x, std::vector<int> y) {
  unsigned int count = std::min(x.size(), y.size());
  for (unsigned int i = 0; i < count; i++) {
    unsigned int j = (i + 1) % count;
    DrawLine(x[i], y[i], x[j], y[j]);
  }
}

void tui::Canvas::DrawPolygon(std::vector<int> points) {
  for (unsigned int i = 0; i < points.size(); i += 2) {
    unsigned int j = (i + 2) % points.size();
    DrawLine(points[i], points[i + 1], points[j], points[j + 1]);
  }
}

void tui::Canvas::DrawFilledPolygon(std::vector<int> x, std::vector<int> y) {
  int min_y = y[0];
  int max_y = y[0];
  for (unsigned int i = 1; i < y.size(); i++) {
    min_y = std::min(min_y, y[i]);
    max_y = std::max(max_y, y[i]);
  }
  for (int i = min_y; i <= max_y; i++) {
    std::vector<int> inter;
    for (unsigned int j = 0; j < x.size() && j < y.size(); j++) {
      unsigned int k = (j + 1) % std::min(x.size(), y.size());
      if (std::max(y[j], y[k]) > i && std::min(y[j], y[k]) <= i) {
        if (x[j] == x[k]) {
          inter.push_back(x[j]);
        } else {
          double m = static_cast<double>(y[k] - y[j]) / (x[k] - x[j]);
          inter.push_back(static_cast<int>((i - y[j] + (m * x[j])) / m));
        }
      }
    }
    for (unsigned int a = 0; a < inter.size(); a += 2) {
      unsigned int b = (a + 2) % inter.size();
      DrawLine(inter[a], i, inter[b], i);
    }
  }
}

void tui::Canvas::DrawFilledPolygon(std::vector<int> points) {
  int min_y = points[1];
  int max_y = points[1];
  for (unsigned int i = 0; i < points.size(); i += 2) {
    max_y = std::max(max_y, points[i + 1]);
    min_y = std::min(min_y, points[i + 1]);
  }
  for (int i = min_y; i <= max_y; i++) {
    std::vector<int> inter;
    for (unsigned int j = 0; j < points.size(); j += 2) {
      unsigned int k = (j + 2) % points.size();
      if ((std::max(points[j + 1], points[k + 1]) > i &&
           std::min(points[j + 1], points[k + 1]) <= i)) {
        if (points[j] == points[k]) {
          inter.push_back(points[j]);
        } else {
          double m = static_cast<double>(points[k + 1] - points[j + 1]) /
                     (points[k] - points[j]);
          inter.push_back(
              static_cast<int>((i - points[j + 1] + (m * points[j])) / m));
        }
      }
    }
    for (unsigned int a = 0; a < inter.size(); a += 2) {
      unsigned int b = (a + 1) % inter.size();
      DrawLine(inter[a], i, inter[b], i);
    }
  }
}

void tui::Canvas::ClearCanvas() {
  for (unsigned i = 0; i < size_[0]; i++) {
    for (unsigned j = 0; j < size_[1]; j++) {
      pixel_data[i][j] = false;
    }
  }
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
  } else if (pixel_format_ == BLOCK || pixel_format_ == SQUARE) {
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
  // Print("%ix%i\n", size_[0], size_[1]);
}

void tui::Canvas::SetPixel(unsigned int x, unsigned int y) {
  if (x > 0 && x < size_[0] && y > 0 && y < size_[1]) {
    pixel_data[x][y] = true;
    DrawPixels(x, y);
  }
}

void tui::Canvas::DrawPixels(unsigned int x, unsigned int y) {
  // static unsigned int count = 0;
  // count++;
  // std::cout << "\n\n>>>>>" << count << "\n";
  unsigned int x_step = 1;
  unsigned int y_step = 1;
  if (pixel_format_ == TWO_BLOCK || pixel_format_ == BLOCK ||
      pixel_format_ == SQUARE) {
    x_step = 1;
    y_step = 1;
  } else if (pixel_format_ == VERTICAL_BLOCK) {
    x_step = 2;
    y_step = 1;
  } else if (pixel_format_ == HORIZONTAL_BLOCK) {
    x_step = 1;
    y_step = 2;
  } else if (pixel_format_ == QUARTER_BLOCK) {
    x_step = 2;
    y_step = 2;
  } else if (pixel_format_ == BRAILLE) {
    x_step = 2;
    y_step = 4;
  }
  if (x % x_step != 0) {
    x = x - (x % x_step);
  }
  if (y % y_step != 0) {
    y = y - (y % y_step);
  }
  if (pixel_format_ == TWO_BLOCK) {
    DrawTwoBlock(x, y);
  } else if (pixel_format_ == SQUARE) {
    DrawSquare(x, y);
  } else if (pixel_format_ == BLOCK) {
    DrawBlock(x, y);
  } else if (pixel_format_ == VERTICAL_BLOCK) {
    DrawVerticalBlock(x, y);
  } else if (pixel_format_ == HORIZONTAL_BLOCK) {
    DrawHorizontalBlock(x, y);
  } else if (pixel_format_ == QUARTER_BLOCK) {
    DrawQuarterBlock(x, y);
  } else if (pixel_format_ == BRAILLE) {
    DrawBraille(x, y);
  }
}

void tui::Canvas::DrawTwoBlock(unsigned int x, unsigned int y) {
  if (pixel_data[x][y] == true) {
    mvPrint((x * 2) + border_active_, window_pos_[3] - y - 2 * border_active_,
            9608);
    mvPrint((x * 2) + 1 + border_active_,
            window_pos_[3] - y - 2 * border_active_, 9608);
  }
}
void tui::Canvas::DrawSquare(unsigned int x, unsigned int y) {
  if (pixel_data[x][y] == true) {
    mvPrint(x + border_active_, window_pos_[3] - y - 2 * border_active_, 9632);
  }
}
void tui::Canvas::DrawBlock(unsigned int x, unsigned int y) {
  if (pixel_data[x][y] == true) {
    mvPrint(x + border_active_, window_pos_[3] - y - 2 * border_active_, 9608);
  }
}
void tui::Canvas::DrawVerticalBlock(unsigned int x, unsigned int y) {
  unsigned int ch = 0;
  if (pixel_data[x][y] == true && pixel_data[x + 1][y] == true) {
    ch = 9608;
  } else if (pixel_data[x][y] == true && pixel_data[x + 1][y] == false) {
    ch = 9612;
  } else if (pixel_data[x][y] == false && pixel_data[x + 1][y] == true) {
    ch = 9616;
  }
  if (ch != 0) {
    mvPrint((x / 2) + border_active_, window_pos_[3] - y - 2 * border_active_,
            ch);
  }
}
void tui::Canvas::DrawHorizontalBlock(unsigned int x, unsigned int y) {
  unsigned int ch = 0;
  if (pixel_data[x][y] == true && pixel_data[x][y + 1] == true) {
    ch = 9608;
  } else if (pixel_data[x][y] == true && pixel_data[x][y + 1] == false) {
    ch = 9604;
  } else if (pixel_data[x][y + 1] == true) {
    ch = 9600;
  }
  if (ch != 0) {
    mvPrint(x + border_active_, window_pos_[3] - (y / 2) - 2 * border_active_,
            ch);
  }
}
void tui::Canvas::DrawQuarterBlock(unsigned int x, unsigned int y) {
  unsigned int ch = 0;
  std::bitset<4> val;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (pixel_data[x + i][y + j] == true) {
        val.set(i + (2 * j));
      }
    }
  }
  std::map<std::string, unsigned int> char_map = {
      {"0000", 0},    {"0001", 9622}, {"0010", 9623}, {"0100", 9624},
      {"1000", 9629}, {"1100", 9600}, {"1010", 9616}, {"1001", 9630},
      {"0110", 9626}, {"0101", 9612}, {"0011", 9604}, {"1110", 9628},
      {"1101", 9627}, {"0111", 9625}, {"1011", 9631}, {"1111", 9608}};
  ch = char_map[val.to_string<char, std::string::traits_type,
                              std::string::allocator_type>()];
  if (ch != 0) {
    mvPrint((x / 2) + border_active_,
            window_pos_[3] - (y / 2) - 2 * border_active_, ch);
  }
}
void tui::Canvas::DrawBraille(unsigned int x, unsigned int y) {
  unsigned int val[2] = {0, 0};
  if (pixel_data[x][y + 3] == true) {
    val[0] += 1;
  }
  if (pixel_data[x][y + 2] == true) {
    val[0] += 2;
  }
  if (pixel_data[x][y + 1] == true) {
    val[0] += 4;
  }
  if (pixel_data[x + 1][y + 3] == true) {
    val[0] += 8;
  }
  if (pixel_data[x + 1][y + 2] == true) {
    val[1] += 1;
  }
  if (pixel_data[x + 1][y + 1] == true) {
    val[1] += 2;
  }
  if (pixel_data[x][y] == true) {
    val[1] += 4;
  }
  if (pixel_data[x + 1][y] == true) {
    val[1] += 8;
  }
  if (val[0] != 0 || val[1] != 0) {
    unsigned int ch = (16 * val[1]) + val[0] + 10240;
    mvPrint((x / 2) + border_active_,
            window_pos_[3] - (y / 4) - 2 * border_active_, ch);
  }
}
