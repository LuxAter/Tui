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
 * @file terminal.hpp
 * @brief Terminal settings
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-01
 */
#ifndef TUI_TERMINAL_TERMINAL_HPP
#define TUI_TERMINAL_TERMINAL_HPP

#include <termios.h>

namespace tui {

  /**
   * @brief Saves current state of the terminal.
   * @sa RestoreTerm
   */
  void SaveTerm();
  /**
   * @brief Restores terminal to previously saved state.
   * @sa SaveTerm
   */
  void RestoreTerm();

  /**
   * @brief Enables echoing.
   * @sa NoEcho
   */
  void Echo();
  /**
   * @brief Disables echoing.
   * @sa Echo
   */
  void NoEcho();

  /**
   * @brief Enables the cursor.
   * @sa NoCursor
   */
  void Cursor();
  /**
   * @brief Disables the cursor.
   * @sa Cursor
   */
  void NoCursor();

  /**
   * @brief Enables raw input.
   * @sa NoRaw
   */
  void Raw();
  /**
   * @brief Diables raw input.
   * @sa Raw
   */
  void NoRaw();

  /**
   * @brief Clears the screen.
   */
  void ClearScreen();
  /**
   * @brief Clears the current line.
   */
  void ClearLine();
}  // namespace tui

#endif /* ifndef TUI_TERMINAL_TERMINAL_HPP */
