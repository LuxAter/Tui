#include "output/attr.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "init.hpp"

namespace tui {
  std::vector<std::string> _active_attrs;
  std::string _active_color = "", _active_background_color = "";
}  // namespace tui

tui::ColorValue::ColorValue() {}
tui::ColorValue::ColorValue(Color color) : id(1), id_enum(color) {}
tui::ColorValue::ColorValue(unsigned char color) : id(2), id_ch(color) {}
tui::ColorValue::ColorValue(unsigned char r, unsigned char g, unsigned char b)
    : id(3), id_r(r), id_g(g), id_b(b) {}
tui::ColorValue::ColorValue(double r, double g, double b) : id(3) {
  id_r = 255 * r;
  id_g = 255 * g;
  id_b = 255 * b;
}
tui::ColorValue::ColorValue(std::initializer_list<unsigned char> l) : id(3) {
  id_r = *(l.begin());
  id_g = *(l.begin() + 1);
  id_b = *(l.begin() + 2);
}
