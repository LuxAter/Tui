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
 * @file keys.hpp
 * @brief Key codes.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-01
 */
#ifndef TUI_INPUT_KEYS_HPP
#define TUI_INPUT_KEYS_HPP

namespace tui {
  /**
   * @brief Key codes
   * 
   * This enum contains representations of all key values that TUI can accept.
   */
  enum KeyCodes {
    KEY_ERR = 0, //!< Invalid Key/No Key
    KEY_ENTER = 10,
    KEY_ESCAPE = 27,
    KEY_SPACE = 32,
    KEY_EXCLAMATION_MARK = 33,
    KEY_QUOTATION_MARK = 34,
    KEY_NUMBER_SIGN = 35,
    KEY_DOLLAR_SIGN = 36,
    KEY_PERCENT_SIGN = 37,
    KEY_AMPERSAND = 38,
    KEY_APOSTROPHE = 39,
    KEY_LEFT_PARENTHESIS = 40,
    KEY_RIGHT_PARENTHESIS = 41,
    KEY_ASTERISK = 42,
    KEY_PLUS = 43,
    KEY_COMMA = 44,
    KEY_MINUS = 45,
    KEY_FULL_STOP = 46,
    KEY_SOLIDUS = 47,
    KEY_ZERO = 48,
    KEY_ONE = 49,
    KEY_TWO = 50,
    KEY_THREE = 51,
    KEY_FOUR = 52,
    KEY_FIVE = 53,
    KEY_SIX = 54,
    KEY_SEVEN = 55,
    KEY_EIGHT = 56,
    KEY_NINE = 57,
    KEY_COLON = 58,
    KEY_SEMICOLON = 59,
    KEY_LESS_THAN_SIGN = 60,
    KEY_EQUALS_SIGN = 61,
    KEY_GREATER_THAN_SIGN = 62,
    KEY_QUESTION_MARK = 63,
    KEY_AT = 64,
    KEY_CAPITAL_A = 65,
    KEY_CAPITAL_B = 66,
    KEY_CAPITAL_C = 67,
    KEY_CAPITAL_D = 68,
    KEY_CAPITAL_E = 69,
    KEY_CAPITAL_F = 70,
    KEY_CAPITAL_G = 71,
    KEY_CAPITAL_H = 72,
    KEY_CAPITAL_I = 73,
    KEY_CAPITAL_J = 74,
    KEY_CAPITAL_K = 75,
    KEY_CAPITAL_L = 76,
    KEY_CAPITAL_M = 77,
    KEY_CAPITAL_N = 78,
    KEY_CAPITAL_O = 79,
    KEY_CAPITAL_P = 80,
    KEY_CAPITAL_Q = 81,
    KEY_CAPITAL_R = 82,
    KEY_CAPITAL_S = 83,
    KEY_CAPITAL_T = 84,
    KEY_CAPITAL_U = 85,
    KEY_CAPITAL_V = 86,
    KEY_CAPITAL_W = 87,
    KEY_CAPITAL_X = 88,
    KEY_CAPITAL_Y = 89,
    KEY_CAPITAL_Z = 90,
    KEY_LEFT_SQUARE_BRACKET = 91,
    KEY_REVERSE_SOLIDUS = 92,
    KEY_RIGHT_SQUARE_BRACKET = 93,
    KEY_CIRCUMFLEX_ACCENT = 94,
    KEY_LOW_LINE = 95,
    KEY_GRAVE_ACCENT = 96,
    KEY_A = 97,
    KEY_B = 98,
    KEY_C = 99,
    KEY_D = 100,
    KEY_E = 101,
    KEY_F = 102,
    KEY_G = 103,
    KEY_H = 104,
    KEY_I = 105,
    KEY_J = 106,
    KEY_K = 107,
    KEY_L = 108,
    KEY_M = 109,
    KEY_N = 110,
    KEY_O = 111,
    KEY_P = 112,
    KEY_Q = 113,
    KEY_R = 114,
    KEY_S = 115,
    KEY_T = 116,
    KEY_U = 117,
    KEY_V = 118,
    KEY_W = 119,
    KEY_X = 120,
    KEY_Y = 121,
    KEY_Z = 122,
    KEY_LEFT_CURLY_BRACKET = 123,
    KEY_VERTICAL_LINE = 124,
    KEY_RIGHT_CURLY_BRACKET = 125,
    KEY_TILDE = 126,
    KEY_BACKSPACE = 127,

    KEY_UP = 128,
    KEY_DOWN = 129,
    KEY_RIGHT = 130,
    KEY_LEFT = 131,
    KEY_DELETE = 132,
  };
}  // namespace tui

#endif /* ifndef TUI_INPUT_KEYS_HPP */
