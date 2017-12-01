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
 * @file init.hpp
 * @brief Core initialization file
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-11-30
 *
 * This file contains the initialization and termination methods for the TUI
 * library.
 */

#ifndef TUI_INIT_HPP
#define TUI_INIT_HPP

#include <string>

#include "window/window.hpp"

/**
 * @brief Core namespace of all TUI functions
 *
 * Every method and member is defined within this namespace to prevent any
 * naming conflicts.
 */
namespace tui {

  /**
   * @brief Type color access enumeration
   *
   * Enum that is used to define the different color access that the current
   * terminal supports.
   */
  enum ColorSets { NO_COLOR = 0, COLOR_16 = 1, COLOR_256 = 2, TRUE_COLOR = 3 };
  /**
   * @brief Flags that can be passed durring initialization.
   *
   * Set of flags to control which functions of the terminal are enabled, or
   * disablabled.
   *
   * @note All of the funcionality of these flags can be achieved by calling
   * other functions.
   */
  enum InitFlags {
    ECHO = 0,
    NO_ECHO = 1,
    RAW = 2,
    NO_RAW = 3,
    CURSOR = 4,
    NO_CURSOR = 5
  };

  /**
   * @brief The standard screen.
   *
   * By default everything is writen to the standard screen, which will then
   * write to the terminal output.
   */
  extern tui::Window stdscr;
  /**
   * @brief The ability of the current terminal to suport colors.
   *
   * On initialization, TUI attemps to determin the ability of the current
   * terminal to display colors.
   */
  extern unsigned int _color_access;
  /**
   * @brief Initializes TUI.
   *
   * This function must be called before any other calls to other TUI functions.
   * It generates the standard screen, and determins the color access of the
   * terminal.
   *
   * @return `true` if it is successfuly initialized, and `false` otherwise.
   */
  bool InitTui();
  /**
   * @brief Terminates TUI.
   *
   * Destroys standard screen, and terminates TUI.
   *
   * @return `true`.
   */
  bool TermTui();
  /**
   * @brief Determins the color capability of the terminal.
   *
   * Determins the color capablity of the current terminal, if any.
   *
   * @return `ColorSets` representing the color ability of terminal.
   */
  int HasColor();

  /**
   * @brief Clears `stdscr`.
   */
  void Clear();

  /**
   * @brief Refreshes `stdscr`.
   */
  void Refresh();

  /**
   * @brief Print wide string to `stdscr`.
   *
   * Print wide string to `stdscr` such as printf.
   *
   * @param str Fmt string.
   * @param ... Additional arguments.
   */
  void Print(std::wstring str, ...);
  /**
   * @brief Print string to `stdscr`.
   *
   * Print string to `stdscr` such as printf.
   *
   * @param str Fmt string.
   * @param ... Additional arguments.
   */
  void Print(std::string str, ...);
  void mvPrint(unsigned x, unsigned y, std::wstring str, ...);
  void mvPrint(unsigned x, unsigned y, std::string str, ...);

  std::wstring GetWString(std::string str);

  tui::Window CreateWindow();
  tui::Window CreateWindow(int w, int h);
  tui::Window CreateWindow(int x, int y, int w, int h);

}  // namespace tui

#endif /* ifndef TUI_INIT_HPP */
