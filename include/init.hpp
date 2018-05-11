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
  enum ColorSets {
    NO_COLOR = 0,   //!< Terminal has no color abbility.
    COLOR_16 = 1,   //!< Terminal can display the base 16 colors.
    COLOR_256 = 2,  //!< Terminal can display 256 different colors.
    TRUE_COLOR = 3  //!< Terminal has true color capability.
  };
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
    ECHO = 0,      //!< Enables echoing of user input.
    NO_ECHO = 1,   //!< Disables echoing of user input.
    RAW = 2,       //!< Enables raw key input.
    NO_RAW = 3,    //!< Disables raw key input.
    CURSOR = 4,    //!< Enables user cursor display.
    NO_CURSOR = 5  //!< Disables user cursor display.
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
   * @todo Enable optional init flags.
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
   * @brief Clears stdscr.
   */
  void Clear();

  /**
   * @brief Refreshes stdscr.
   */
  void Refresh();

  /**
   * @brief Print wide string to stdscr.
   *
   * Print wide string to stdscr such as printf.
   *
   * @param str Fmt string.
   * @param ... Additional arguments.
   */
  void Print(std::wstring str, ...);
  /**
   * @brief Print string to stdscr.
   *
   * Print string to stdscr such as printf.
   *
   * @param str Fmt string.
   * @param ... Additional arguments.
   */
  void Print(std::string str, ...);
  /**
   * @brief Prints at given position wide string to stdscr.
   * Move cursor to specified position and prints the supplied wide string, and
   * additional arguments to stdscr.
   * @param x X position to move the cursor to.
   * @param y Y position to move the cursor to.
   * @param str  Fmt string.
   * @param ... Additional arguments.
   */
  void mvPrint(unsigned x, unsigned y, std::wstring str, ...);
  /**
   * @brief Prints at given position string to stdscr.
   * Move cursor to specified position and prints the supplied string, and
   * additional arguments to stdscr.
   * @param x X position to move the cursor to.
   * @param y Y position to move the cursor to.
   * @param str  Fmt string.
   * @param ... Additional arguments.
   */
  void mvPrint(unsigned x, unsigned y, std::string str, ...);

  /**
   * @brief Converts string to wide string.
   *
   * Taks a provided string and converts to the associated wide string
   * alternative.
   *
   * @todo Add ability to intelegently read unicode representations in normal
   * string to wide string alternatives.
   *
   * @param str String to convert.
   *
   * @return Wide string containg data converted from `str`.
   */
  std::wstring GetWString(std::string str);

  /**
   * @brief Generates window.
   *
   * Generates a window with the same dimensions as stdscr.
   *
   * @return Window object.
   */
  tui::Window CreateWindow();
  /**
   * @brief Generates window.
   *
   * Generates a window at (0,0) with the provided dimensions.
   *
   * @param w Width of generated window.
   * @param h Height of generated window.
   *
   * @return Window object.
   */
  tui::Window CreateWindow(int w, int h);
  /**
   * @brief Generates window.
   *
   * Generates a window at provided position with provided dimensions.
   *
   * @param x Position of window.
   * @param y Position of window.
   * @param w Width of window.
   * @param h Height of window.
   *
   * @return Window object.
   */
  tui::Window CreateWindow(int x, int y, int w, int h);

}  // namespace tui

#endif /* ifndef TUI_INIT_HPP */
