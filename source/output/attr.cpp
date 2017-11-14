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

void tui::AttrOn(Attr attr) {
  if (attr == NONE) {
    _active_attrs.clear();
  }
  unsigned int attr_int = static_cast<unsigned int>(attr);
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "\033[%im", attr_int);
  _active_attrs.push_back(std::string(buffer));
}

void tui::AttrOff(Attr attr) {
  unsigned int attr_int = static_cast<unsigned int>(attr);
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "\033[%im", attr_int);
  std::string match(buffer);
  for (unsigned int i = 0; i < _active_attrs.size(); i++) {
    if (_active_attrs[i] == match) {
      _active_attrs.erase(_active_attrs.begin() + i);
      break;
    }
  }
}

void tui::SetColor(ColorPair color) {
  SetColor(color.fg);
  SetBackground(color.bg);
}
void tui::SetColor(ColorValue color) {
  if (color.id == 1) {
    SetColor(color.id_enum);
  } else if (color.id == 2) {
    SetColor(color.id_ch);
  } else if (color.id == 3) {
    SetColor(color.id_r, color.id_g, color.id_b);
  }
}
void tui::SetColor(Color color) {
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

void tui::SetBackground(ColorValue color) {
  if (color.id == 1) {
    SetBackground(color.id_enum);
  } else if (color.id == 2) {
    SetBackground(color.id_ch);
  } else if (color.id == 3) {
    SetBackground(color.id_r, color.id_g, color.id_b);
  }
}
void tui::SetBackground(Color color) {
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
