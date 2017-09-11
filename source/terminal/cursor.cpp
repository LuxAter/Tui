#include "terminal/cursor.hpp"

void tui::GetCursor(int& x, int& y) {
  x = cursor_position_[0];
  y = cursor_position_[1];
}

void tui::MoveCursor(int x, int y) {
  cursor_position_[0] += x;
  cursor_position_[1] += y;
}

void tui::SetCursor(int x, int y) {
  cursor_position_[0] = x;
  cursor_position_[1] = y;
}
