// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/keyboard.h>

namespace scalepiegraph {

namespace frontend {

Keyboard::Keyboard(const glm::vec2& bottom_left_corner,
                   float width,
                   float height,
                   size_t num_divisions) :
    bottom_left_corner_(bottom_left_corner),
    width_(width),
    height_(height),
    current_divisions_(num_divisions) {}

void Keyboard::Draw() {
  // Draw bounding box
  ci::gl::drawStrokedRect(ci::Rectf(
      glm::vec2(bottom_left_corner_.x, bottom_left_corner_.y - height_),
      glm::vec2(bottom_left_corner_.x + width_, bottom_left_corner_.y)));

  for (size_t div_idx = 0; div_idx < current_divisions_; ++div_idx) {
    float width_unit = width_ / current_divisions_;

    glm::vec2 upper_left_corner(
        div_idx * width_unit, bottom_left_corner_.y - height_);
    glm::vec2 lower_right_corner(
        div_idx * width_unit + 1, bottom_left_corner_.y);

    ci::gl::drawStrokedRect(ci::Rectf(upper_left_corner, lower_right_corner));
  }
}

void Keyboard::UpdateDivisions(size_t num_divisions) {
  current_divisions_ = num_divisions;
}

}

}