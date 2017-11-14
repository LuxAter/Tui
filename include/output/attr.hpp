#ifndef TUI_OUTPUT_ATTR_HPP_
#define TUI_OUTPUT_ATTR_HPP_

#include <initializer_list>
#include <string>
#include <vector>

namespace tui {

  enum Attr {
    NONE = 0,
    BOLD = 1,
    FAINT = 2,
    ITALIC = 3,
    UNDERLINE = 4,
    BLINK = 5,
    REVERSE = 7,
    CONCEAL = 8,
    CROSS_OUT = 9
  };
  enum Color {
    DEFAULT = 0,
    BLACK = 1,
    RED = 2,
    GREEN = 3,
    YELLOW = 4,
    BLUE = 5,
    MAGENTA = 6,
    CYAN = 7,
    LIGHT_GREY = 8,
    DARK_GREY = 9,
    LIGHT_RED = 10,
    LIGHT_GREEN = 11,
    LIGHT_YELLOW = 12,
    LIGHT_BLUE = 13,
    LIGHT_MAGENTA = 14,
    LIGHT_CYAN = 15,
    WHITE = 16
  };

  extern std::vector<std::string> _active_attrs;
  extern std::string _active_color, _active_background_color;

  struct ColorValue {
    ColorValue();
    ColorValue(Color color);
    ColorValue(unsigned char color);
    ColorValue(unsigned char r, unsigned char g, unsigned char b);
    ColorValue(double r, double g, double b);
    ColorValue(std::initializer_list<unsigned char> l);
    unsigned int id = 0;
    Color id_enum;
    unsigned char id_ch;
    unsigned id_r, id_g, id_b;
  };
  struct ColorPair {
    ColorValue fg, bg;
  };

  void AttrOn(Attr attr);
  void AttrOff(Attr attr);
  void SetColor(ColorPair color);
  void SetColor(Color color);
  void SetColor(ColorValue color);
  void SetColor(unsigned char color);
  void SetColor(unsigned char r, unsigned char g, unsigned char b);
  void SetBackground(Color color);
  void SetBackground(ColorValue color);
  void SetBackground(unsigned char color);
  void SetBackground(unsigned char r, unsigned char g, unsigned char b);

}  // namespace tui

#endif  // TUI_OUTPUT_ATTR_HPP_
