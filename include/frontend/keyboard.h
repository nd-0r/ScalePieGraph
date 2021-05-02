// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <cinder/gl/gl.h>

namespace scalepiegraph {

namespace frontend {

/**
 * A class representing a keyboard to use as onscreen input to
 * trigger a synthesizer.
 */
class Keyboard {
 public:
  /**
   * Construct a keyboard with all default values. Cannot be drawn.
   */
  Keyboard() = default;

  /**
   * Construct a Keyboard in the specified location with the specified width,
   * height, and number of divisions.
   *
   * @param bottom_left_corner The location of the bottom left corner
   * @param width The width of the keyboard
   * @param height The height of the keyboard
   * @param num_divisions The number of divisions of the keyboard
   */
  Keyboard(const glm::vec2& bottom_left_corner,
           float width,
           float height,
           size_t num_divisions);

  /**
   * Draw this keyboard.
   */
  void Draw();

  /**
   * Get the key index corresponding to the current position of the mouse, or -1
   * if the mouse is not in the bounds of a key.
   *
   * @param mouse_pos The current coordinates of the mouse pointer
   * @return The key index if found; otherwise, -1
   */
   int GetKeyIndex(const glm::vec2& mouse_pos) const;

  /**
   * Update the number of divisions of this keyboard to the specified number.
   *
   * @param num_divisions The new number of divisions for this keyboard
   */
  void UpdateDivisions(size_t num_divisions);

 private:
  glm::vec2 bottom_left_corner_;
  float width_;
  float height_;
  size_t current_divisions_;
};

}

}