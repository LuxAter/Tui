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
 * @file event.hpp
 * @brief Event handeling system
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-11
 */
#ifndef TUI_INPUT_EVENT_HPP_
#define TUI_INPUT_EVENT_HPP_

#include <string>
#include <vector>

#include "event_class.hpp"

namespace tui {

  /**
   * @brief Number of miliseconds to wait for inputs.
   *
   * The defaulting number of milliseconds to wait for an input, if the value is
   * negetive, then the function will wait indefinently for user input.
   */
  extern int timeout_;

  /**
   * @brief Get next event.
   *
   * Returns the next event in the FIFO sequence that there were read in from.
   * Returns a valid event with `type=NONE_EVENT` if there are no more events.
   *
   * @return tui::Event of the next event in the sequence.
   */
  tui::Event PopEvent();
  /**
   * @brief Polls events and returns the first one in the sequence.
   *
   * Looks for more events to read with no wait delay, then returns the first
   * event in the sequence.
   *
   * @note The first event may not be a new event read in, But could be an old
   * event that was waiting in the queue.
   *
   * @return tui::Event of the next event in the sequence.
   */
  tui::Event GetEvent();
  /**
   * @brief Polls events and returns the first valid mouse event.
   *
   * Looks for more events to read with no wait delay, then removes events from
   * the event queue, until ther are no more, or until a mouse event has been
   * reached.
   *
   * @return tui::Event::MouseEvent of first valid mouse event, or an invalid
   * mouse event if none exist in the queue.
   */
  tui::Event::MouseEvent GetMouseEvent();
  /**
   * @brief Polls events and returns the first valid keyboard event.
   *
   * Looks for more events to read with no wait delay, then removes events from
   * the event queue, until ther are no more, or until a keyboard event has been
   * reached.
   *
   * @return tui::Event::KeyboardEvent of first valid keyboard event, or an
   * invalid
   * keyboard event if none exist in the queue.
   */
  tui::Event::KeyboardEvent GetKeyboardEvent();

  /**
   * @brief Returns first valid event until timeout time has been reached.
   *
   * Either returns the next event in the queue, or if the queue is empty, wait
   * until the timeout duration for an event to be input, then returns the first
   * input event. Or an invalid event if no event was passed by the end of the
   * timeout period.
   *
   * @param timeout Milliseconds to wait for user input event.
   *
   * @return tui::Event `valid` if an event is waiting or user enters event
   * before timeout, `invalid` if user does not enter event before timeout.
   */
  tui::Event WaitEvent(int timeout = timeout_);
  /**
   * @brief Returns first valid mouse event until timeout time has been reached.
   *
   * Either returns the next valid mouse event from the queue, or waits until
   * the timeout duration for the user to enter a mouse event, then returns the
   * fist input event.
   *
   * @param timeout Milliseconds to wait for user input event.
   *
   * @return tui::Event::MouseEvent `valid` if an event is found, `invalid` if
   * no event is entered in time.
   */
  tui::Event::MouseEvent WaitMouseEvent(int timeout = timeout_);
  /**
   * @brief Returns thre first valid keyboard event until timeout time has been
   * reached.
   *
   * Either returns the next valid keyboard event from the queue, or waits until
   * the timeout duration for the user to enter a keyboard event, then returns
   * the first input event.
   *
   * @param timeout Milliseconds to wait for user input event.
   *
   * @return tui::Event::KeyboardEvent `valid` if an event is found, `invalid`
   * if no event is entered in time.
   */
  tui::Event::KeyboardEvent WaitKeyboardEvent(int timeout = timeout_);
  /**
   * @brief Returns key from keyboard event, or `KEY_ERR`.
   *
   * @param timeout Milliseconds to wait for user input.
   *
   * @return Value of key, or `KEY_ERR` if no key is pressed.
   */
  unsigned int GetCh(int timeout = timeout_);

  /**
   * @brief Reads all characters input into events.
   *
   * @param timeout_ms Time to wait for event input.
   */
  void PollEvents(int timeout_ms);
  /**
   * @brief Determins the number of characters waiting in `stdin`.
   *
   * @param timeout_ms Time to wait for characters in milliseconds.
   *
   * @return The number of characters buffered in `stdin`.
   */
  unsigned int PendingEvents(int timeout_ms);

  /**
   * @brief Parses character queue for events.
   *
   * Parses the entire character queue for events, Reading all the characters
   * into event objects. This function is automatticaly calles by
   * tui::PollEvents, so should not be called manualy.
   */
  void ReadEvent();
  /**
   * @brief Parses character queue for mouse event.
   *
   * This function should be avoided, as all event systems are handeled
   * internaly.
   *
   * @return tui::Event::MouseEvent representing the sequence of characters.
   */
  tui::Event::MouseEvent ReadMouseEvent();
  /**
   * @brief Parses character queue for keyboard event.
   *
   * This function should be avoided, as all event systems are handeled
   * internaly.
   *
   * @param start Flag if starting character was `91`.
   *
   * @return tui::Event::KeyboardEvent represeting the sequence of characters.
   */
  tui::Event::KeyboardEvent ReadKeyBoardEvent(bool start);
  /**
   * @brief Pops next character from character input queue.
   *
   * This function should be called as little as posible as all event systems
   * are handeled internaly, and this should always return `0`.
   *
   * @return Next input character.
   */
  unsigned int PopCharacter();

  /**
   * @brief Sets the default timeout period.
   *
   * Sets the default milliseconds to wait until returning an `invalid` event.
   *
   * @param timeout Time in milliseconds.
   * @sa tui::GetCh tui::WaitEvent tui::WaitMouseEvent tui::WaitKeyboardEvent
   */
  void SetTimeout(int timeout);
  /**
   * @brief Gets the currently set timeout period.
   *
   * @return timeout durration in milliseconds.
   */
  int GetTimeout();
}  // namespace tui

#endif  // TUI_INPUT_EVENT_HPP_
