#include "output/attr.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "init.hpp"

namespace tui {
  std::vector<std::string> _active_attrs;
  std::string _active_color = "", _active_background_color = "";
}  // namespace tui

tui::Color::Color() {}
tui::Color::Color(Color_ color) : id(1), id_enum(color) {}
tui::Color::Color(unsigned char color) : id(2), id_ch(color) {}
tui::Color::Color(unsigned char r, unsigned char g, unsigned char b)
    : id(3), id_r(r), id_g(g), id_b(b) {}
tui::Color::Color(double r, double g, double b) : id(3) {
  id_r = 255 * r;
  id_g = 255 * g;
  id_b = 255 * b;
}
tui::Color::Color(std::initializer_list<unsigned char> l) : id(3) {
  id_r = *(l.begin());
  id_g = *(l.begin() + 1);
  id_b = *(l.begin() + 2);
}
// tui::Color::Color(std::initializer_list<double> l) : id(3) {
// id_r = 255 * *(l.begin());
// id_g = 255 * *(l.begin() + 1);
// id_b = 255 * *(l.begin() + 2);
// }

void tui::SetAttr(Attr_ attr) {}
void tui::SetColor(ColorPair color) {
  SetColor(color.fg);
  SetBackground(color.bg);
}
void tui::SetColor(Color color) {
  if (color.id == 1) {
    SetColor(color.id_enum);
  } else if (color.id == 2) {
    SetColor(color.id_ch);
  } else if (color.id == 3) {
    SetColor(color.id_r, color.id_g, color.id_b);
  }
}
void tui::SetColor(Color_ color) {
  if (_color_access == COLOR_16 || _color_access == COLOR_256 ||
      _color_access == TRUE_COLOR) {
    if (color == DEFAULT) {
      _active_color = "\033[39m";
    } else {
      unsigned int color_int = static_cast<unsigned int>(color);
      if (color_int > 8) {
        color_int += 52;
      }
      color_int += 29;
      char buffer[50];
      snprintf(buffer, sizeof(buffer), "\033[%im", color_int);
      _active_color = std::string(buffer);
    }
  } else {
    std::cerr << "Current terminal does not support colors\n";
  }
}
void tui::SetColor(unsigned char color) {
  if (_color_access == COLOR_256 || _color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[38;5;%im", color);
    _active_color = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support 256 colors\n";
  }
}
void tui::SetColor(unsigned char r, unsigned char g, unsigned char b) {
  if (_color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[38;2;%i;%i;%im", r, g, b);
    _active_color = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support true colors\n";
  }
}

void tui::SetBackground(Color color) {
  if (color.id == 1) {
    SetBackground(color.id_enum);
  } else if (color.id == 2) {
    SetBackground(color.id_ch);
  } else if (color.id == 3) {
    SetBackground(color.id_r, color.id_g, color.id_b);
  }
}
void tui::SetBackground(Color_ color) {
  if (_color_access == COLOR_16 || _color_access == COLOR_256 ||
      _color_access == TRUE_COLOR) {
    if (color == DEFAULT) {
      _active_background_color = "\033[49m";
    } else {
      unsigned int color_int = static_cast<unsigned int>(color);
      if (color_int > 8) {
        color_int += 52;
      }
      color_int += 39;
      char buffer[50];
      snprintf(buffer, sizeof(buffer), "\033[%im", color_int);
      _active_background_color = std::string(buffer);
    }
  } else {
    std::cerr << "Current terminal does not support colors\n";
  }
}
void tui::SetBackground(unsigned char color) {
  if (_color_access == COLOR_256 || _color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[48;5;%im", color);
    _active_background_color = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support 256 colors\n";
  }
}
void tui::SetBackground(unsigned char r, unsigned char g, unsigned char b) {
  if (_color_access == TRUE_COLOR) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "\033[48;2;%i;%i;%im", r, g, b);
    _active_background_color = std::string(buffer);
  } else {
    std::cerr << "Current terminal does not support true colors\n";
  }
}
