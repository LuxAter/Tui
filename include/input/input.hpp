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
 * @file input.hpp
 * @brief User terminal input functions.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-01
 */

#ifndef TUI_INPUT_INPUT_HPP
#define TUI_INPUT_INPUT_HPP

namespace tui {

  /**
   * @brief Sets input timeout in ms.
   *
   * This is used to determin the time to wait for user input before timinging
   * out and returning. Should always be set through SetTimeout.
   *
   * @sa SetTimeout
   */
  extern int timeout_;

  /**
   * @brief Requests user character input.
   *
   * Reads from input stream until either the timeout_ time has been reached, or
   * untill the user presses a key.
   *
   * @return KeyCodes representation of the key pressed by the user, or
   * tui::KeyCodes::ERR if no key was pressed.
   *
   * @sa KeyCodes
   */
  unsigned int getch();
  /**
   * @brief Waits until a key has been hit.
   *
   * Waites until a key has been pressed or the timeout_ time has been reached.
   *
   * @param timeout_ms Time in milliseconds to wait for key press.
   *
   * @return `true` if a key was pressed, and `false` if no key was pressed.
   */
  bool kbhit(int timeout_ms = timeout_);
  /**
   * @brief Returns coresponding key code for char.
   *
   * @param key char to key representative key code.
   *
   * @return KeyCodes representation of key.
   */
  unsigned int GetKeyCode(char key);
  /**
   * @brief Parses escaped key codes.
   *
   * Parses the data of an escaped key press (arrow keys, delete, etc.), and
   * finds the coresponding KeyCodes value.
   *
   * @param key escaped char.
   *
   * @return KeyCodes representing the escape code.
   */
  unsigned int GetEscapeKey(char key);

  /**
   * @brief Sets the timeout in milliseconds.
   *
   * Sets the timeout_ time, that getch() will wait until returning.
   *
   * @param timeout Time in milliseconds.
   */
  void SetTimeout(int timeout);
}  // namespace tui

#endif /* ifndef TUI_INPUT_INPUT_HPP */
