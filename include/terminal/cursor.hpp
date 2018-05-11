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
 * @file cursor.hpp
 * @brief Cursor movement control
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-01
 */
#ifndef TUI_TERMINAL_CURSOR_HPP
#define TUI_TERMINAL_CURSOR_HPP

namespace tui {
  /**
   * @brief Contains the position of the cursor.
   */
  static int cursor_position_[2] = {0, 0};

  /**
   * @brief Returns the current position of the cursor.
   *
   * @param x stores x position.
   * @param y sotres y position.
   */
  void GetCursor(int& x, int& y);
  /**
   * @brief Moves the cursor.
   *
   * Moves the cursor relative the the current position.
   * 
   * @param x X position of the cursor.
   * @param y Y position of the cursor.
   */
  void MoveCursor(int x, int y);
  /**
   * @brief Sets the cursor position
   *
   * @param x Absolute X position of the cursor.
   * @param y Absolute Y position of the cursor.
   */
  void SetCursor(int x, int y);
}  // namespace tui

#endif /* ifndef TUI_TERMINAL_CURSOR_HPP */
