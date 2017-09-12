#include "output/buffer.hpp"

#include <stdio.h>

void tui::SwapBuffers() {
  int width = display_buffer_.size();
  int height = display_buffer_[0].size();
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (display_buffer_[x][y] != write_buffer_[x][y]) {
        display_buffer_[x][y] = write_buffer_[x][y];
        printf("\033[%i;%iH%c", y + 1, x + 1, display_buffer_[x][y]);
      }
    }
  }
}

void tui::Refresh() { SwapBuffers(); }

void tui::Write(unsigned int x, unsigned int y, const char* str, int length) {
  unsigned int head[2] = {x, y};
  for (int i = 0; i < length; i++) {
    write_buffer_[head[0]][head[1]] = str[i];
    head[0]++;
    if (head[0] >= write_buffer_.size()) {
      head[0] = 0;
      head[1]++;
    }
  }
}
