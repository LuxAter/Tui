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

// TODO(2017-12-14, Arden): Add erase point, line, rect, triangle commands.
// TODO(2017-12-14, Arden): Clear canvas when points are cleared.

/**
 * @file canvas.hpp
 * @brief Canvas drawing
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-02
 */
#ifndef TUI_CANVAS_HPP_
#define TUI_CANVAS_HPP_

#include <array>
#include <bitset>
#include <string>
#include <vector>

#include "window.hpp"

namespace tui {

  /**
   * @brief Sets the format for canvas drawing pixels.
   *
   * Uses the different formats for different "Resolutions".
   */
  enum PixelFormat {
    TWO_BLOCK,
    SQUARE,
    BLOCK,
    VERTICAL_BLOCK,
    HORIZONTAL_BLOCK,
    QUARTER_BLOCK,
    BRAILLE
  };

  /**
   * @brief Canvas drawing object class.
   *
   * Canvas for drawing images and shapes to the terminal, through setting
   * pixels, and basic rendering primitives.
   */
  class Canvas : public tui::Window {
   public:
    /**
     * @brief Default constructor.
     */
    Canvas();
    /**
     * @brief Constructor.
     *
     * Generates canvas object of given width, and height, at the origin.
     *
     * @param w Width of canvas.
     * @param h Height of canvas.
     */
    Canvas(int w, int h);
    /**
     * @brief Constructor.
     *
     * Generates canvas object of given width and height, at the given position.
     *
     * @param x X position of the canvas.
     * @param y Y position of the canvas.
     * @param w Width of the canvas.
     * @param h Height of the canvas.
     */
    Canvas(int x, int y, int w, int h);
    /**
     * @brief Copy constructor.
     *
     * Copies the provided canvas.
     *
     * @param rhs Canvas to copy.
     */
    Canvas(const Canvas& rhs);

    /**
     * @brief Sets the pixel format of the canvas.
     *
     * @param format Format to set the pixels to.
     *
     * @sa PixelFormat
     */
    void SetPixel(PixelFormat format);
    /**
     * @brief Sets the origin of the canvas.
     *
     * Used to shift the position of (0,0) to anywhere in the grid.
     *
     * @param x X position of orign.
     * @param y Y position of origin.
     */
    void SetOrigin(int x, int y);
    /**
     * @brief Sets the relative position of the orign of the canvas.
     *
     * Used to shift the positoin of (0,0) to some relative position on the
     * canvas. Where 0 is the left and 1.0 is the right most position on the
     * canvas. Example: (0.5, 0.5) to set to the center of the canvas.
     *
     * @param x X position of origin.
     * @param y Y position of origin.
     */
    void SetOrigin(double x, double y);

    /**
     * @brief Draws a single point.
     *
     * @param x X position of point.
     * @param y Y position of point.
     */
    void DrawPoint(int x, int y);
    /**
     * @brief Draws a line.
     *
     * @param ax Start x position of line.
     * @param ay Start y position of line.
     * @param bx End x position of line.
     * @param by End y position of line.
     */
    void DrawLine(int ax, int ay, int bx, int by);
    /**
     * @brief Draw triangle.
     *
     * @param ax First point x position.
     * @param ay First point y position.
     * @param bx Second point x position.
     * @param by Second point y position.
     * @param cx Third point x position.
     * @param cy Third point y position.
     */
    void DrawTriangle(int ax, int ay, int bx, int by, int cx, int cy);
    /**
     * @brief Draws a filled triangle
     *
     * @param ax First point x position.
     * @param ay First point y position.
     * @param bx Second point x position.
     * @param by Second point y position.
     * @param cx Third point x position.
     * @param cy Third point y position.
     */
    void DrawFilledTriangle(int ax, int ay, int bx, int by, int cx, int cy);
    /**
     * @brief Draws a rectangle.
     *
     * @param ax First point x position.
     * @param ay First point y position.
     * @param bx Second point x position.
     * @param by Second point y position.
     * @param cx Third point x position.
     * @param cy Third point y position.
     * @param dx Fourth point x position.
     * @param dy Fourth point y position.
     */
    void DrawRectangle(int ax, int ay, int bx, int by, int cx, int cy, int dx,
                       int dy);
    /**
     * @brief Draws a filled rectangle.
     *
     * @param ax First point x position.
     * @param ay First point y position.
     * @param bx Second point x position.
     * @param by Second point y position.
     * @param cx Third point x position.
     * @param cy Third point y position.
     * @param dx Fourth point x position.
     * @param dy Fourth point y position.
     */
    void DrawFilledRectangle(int ax, int ay, int bx, int by, int cx, int cy,
                             int dx, int dy);
    /**
     * @brief Draws a circle.
     *
     * @param x X position of the center of the circle.
     * @param y Y position of the center of the circle.
     * @param r Radius of the circle.
     */
    void DrawCircle(int x, int y, int r);
    /**
     * @brief Draws a filled circle.
     *
     * @param x X position of the center of the circle.
     * @param y Y position of the center of the circle.
     * @param r Radius of the circle.
     */
    void DrawFilledCircle(int x, int y, int r);
    /**
     * @brief Draws a regular sided polygon.
     *
     * @param x X position of the center of the polygon.
     * @param y Y position of the center of the polygon.
     * @param r Radius of the polygon.
     * @param n Number of verticies.
     */
    void DrawRegularPolygon(int x, int y, int r, int n);
    /**
     * @brief Draws a filled regular sided polygon.
     *
     * @param x X position of the center of the polygon.
     * @param y Y position of the center of the polygon.
     * @param r Radius of the polygon.
     * @param n Number of verticies.
     */
    void DrawFilledRegularPolygon(int x, int y, int r, int n);
    /**
     * @brief Draws a polygon given points.
     *
     * @param x Vector of x positions of the points in the polygon.
     * @param y Vector of y positions of the points in the polygon.
     */
    void DrawPolygon(std::vector<int> x, std::vector<int> y);
    /**
     * @brief Draws a polygon given points.
     *
     * @param points (x,y) positions of the points in the polygon.
     */
    void DrawPolygon(std::vector<int> points);
    /**
     * @brief Draws a filled polygon given points.
     *
     * @param x Vector of x positions of the points in the polygon.
     * @param y Vector of y positions of the points in the polygon.
     */
    void DrawFilledPolygon(std::vector<int> x, std::vector<int> y);
    /**
     * @brief Draws a filled polygon given points.
     *
     * @param points (x,y) positions of the points in the polygon.
     */
    void DrawFilledPolygon(std::vector<int> points);
    /**
     * @brief Clears all points from the canvas grid.
     */
    void ClearCanvas();

    /**
     * @brief Enables the canvas buffer's border protection.
     */
    void EnableBorder();
    /**
     * @brief Disables the canvas buffer's border protection.
     */
    void DisableBorder();

    /**
     * @brief Get the maximum x position of the canvas.
     *
     * @return Maximum x position on the canvas.
     */
    int MaxX();
    /**
     * @brief Get the minmum x position of the canvas.
     *
     * @return Minmum x position on the canvas.
     */
    int MinX();
    /**
     * @brief Get the maximum y position of the canvas.
     *
     * @return Maximum y position on the canvas.
     */
    int MaxY();
    /**
     * @brief Get the minmum y position of the canvas.
     *
     * @return Minmum y position on the canvas.
     */
    int MinY();

   private:
    void ResizeGrid();
    void SetPixel(unsigned int x, unsigned int y);
    void DrawPixels(unsigned int x, unsigned int y);

    void DrawTwoBlock(unsigned int x, unsigned int y);
    void DrawSquare(unsigned int x, unsigned int y);
    void DrawBlock(unsigned int x, unsigned int y);
    void DrawVerticalBlock(unsigned int x, unsigned int y);
    void DrawHorizontalBlock(unsigned int x, unsigned int y);
    void DrawQuarterBlock(unsigned int x, unsigned int y);
    void DrawBraille(unsigned int x, unsigned int y);

    unsigned int pixel_format_ = BLOCK;
    std::vector<std::vector<bool>> pixel_data;
    std::array<unsigned int, 2> size_ = {{1, 1}};
    std::array<int, 2> origin_ = {{0, 0}};
  };
}  // namespace tui

#endif  // TUI_CANVAS_HPP_
