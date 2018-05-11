/* Copyright (C) 
 * 2017 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

/**
 * @file attr.hpp
 * @brief Output attributes
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-01
 */
#ifndef TUI_OUTPUT_ATTR_HPP_
#define TUI_OUTPUT_ATTR_HPP_

#include <initializer_list>
#include <string>
#include <vector>

namespace tui {

  /**
   * @brief Posible attributes to apply to output text.
   */
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
  /**
   * @brief Posible default colors to apply to output text.
   */
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

  /**
   * @brief Representation of some color.
   * 
   * Can be created from either the Color enum, or from some Red, Green, and Blue values.
   */
  struct ColorValue {
    /**
     * @brief Default constructor.
     * 
     * Generates black color.
     */
    ColorValue();
    /**
     * @brief Constructor
     *
     * @param color Color enum to use.
     */
    ColorValue(Color color);
    /**
     * @brief Constructor
     *
     * @param color Ansi escape code to use for color from (0-256)
     */
    ColorValue(unsigned char color);
    /**
     * @brief Constructor
     * 
     * Generates color from 256 bit red, green, and blue values.
     *
     * @param r (0-256)
     * @param g (0-256)
     * @param b (0-256)
     */
    ColorValue(unsigned char r, unsigned char g, unsigned char b);
    /**
     * @brief Constructor
     * 
     * Generates color from 0-1 floating red, green, and blue values.
     *
     * @param r (0-1)
     * @param g (0-1)
     * @param b (0-1)
     */
    ColorValue(double r, double g, double b);
    /**
     * @brief Constructor
     * 
     * Generates color from 256 bit red, green, and blue values.
     *
     * @param l Initializer list of color values.
     */
    ColorValue(std::initializer_list<unsigned char> l);
    /**
     * @brief Contains the format that the color is represented with.
     */
    unsigned int id = 0;
    /**
     * @brief Color enum representing the color.
     */
    Color id_enum;
    /**
     * @brief 256 bit integer color representation.
     */
    unsigned char id_ch;
    /**
     * @brief 256 bit integer red color representation.
     */
    unsigned char id_r;
    /**
     * @brief 256 bit integer green color representation.
     */
    unsigned char id_g;
    /**
     * @brief 256 bit integer blue color representation.
     */
    unsigned char id_b;
  };
  /**
   * @brief Pair of colors for foreground and background.
   * 
   * @sa ColorValue
   */
  struct ColorPair {
    /**
     * @brief Foreground color.
     * 
     * @sa ColorValue
     */
    ColorValue fg;
    /**
     * @brief Background Color.
     * 
     * @sa ColorValue
     */
    ColorValue bg;
  };

}  // namespace tui

#endif  // TUI_OUTPUT_ATTR_HPP_
