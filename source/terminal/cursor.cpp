#include "terminal/cursor.hpp"

void tui::GetCursor(int& x, int& y) {
  x = cursor_position_[0];
  y = cursor_position_[1];
}
