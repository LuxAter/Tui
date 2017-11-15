#include "window/canvas.hpp"

#include <array>
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

void tui::Canvas::DrawPoint(unsigned int x, unsigned int y) {
  if (x < pixel_data.size() && y < pixel_data[x].size()) {
    pixel_data[x][y] = true;
  }
  DrawPixels();
}

unsigned int tui::Canvas::MaxX() { return pixel_data.size(); }

unsigned int tui::Canvas::MaxY() { return pixel_data[0].size(); }

void tui::Canvas::ResizeGrid() {
  double x_char = 0, y_char = 0;
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
  } else if (pixel_format_ == BRAIL) {
    x_char = 2;
    y_char = 4;
  }
  int size_x = (window_pos_[2] - 2 * border_active_) * x_char,
      size_y = (window_pos_[3] - 2 * border_active_) * y_char;
  pixel_data.resize(size_x);
  for (unsigned int i = 0; i < pixel_data.size(); i++) {
    pixel_data[i].resize(size_y);
  }
  // Print("%ix%i\n", window_pos_[2], window_pos_[3]);
  // Print("%ix%i\n", size_x, size_y);
}

void tui::Canvas::DrawPixels() {
  if (pixel_format_ == BLOCK) {
    for (unsigned int i = 0; i < pixel_data.size(); i++) {
      for (unsigned int j = 0; j < pixel_data[i].size(); j++) {
        if (pixel_data[i][j] == true) {
          mvPrint(i + border_active_, window_pos_[3] - (j + border_active_),
                  9608);
        }
      }
    }
  }
}
