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
    current_divisions_(num_divisions) {
  CreateKeys(false);
}

void Keyboard::Draw() {
  // Draw bounding box
  ci::gl::drawStrokedRect(ci::Rectf(
      glm::vec2(bottom_left_corner_.x, bottom_left_corner_.y - height_),
      glm::vec2(bottom_left_corner_.x + width_, bottom_left_corner_.y)));

  CreateKeys(true);
}

int Keyboard::GetKeyIndex(const glm::vec2& mouse_pos) const {
  int key_idx = 0;

  for (const ci::Path2d& key : keys_) {
    if (key.contains(mouse_pos)) {
      return key_idx;
    }

    ++key_idx;
  }

  return -1; // Position is not inside a key
}

void Keyboard::UpdateDivisions(size_t num_divisions) {
  current_divisions_ = num_divisions;
}

void Keyboard::CreateKeys(bool should_draw) {
  keys_ = std::vector<ci::Path2d>();

  for (size_t div_idx = 0; div_idx < current_divisions_; ++div_idx) {
    float width_unit = width_ / current_divisions_;

    glm::vec2 upper_left_corner(
        div_idx * width_unit, bottom_left_corner_.y - height_);
    glm::vec2 upper_right_corner(
        (div_idx + 1) * width_unit, bottom_left_corner_.y - height_);
    glm::vec2 lower_right_corner(
        (div_idx + 1) * width_unit, bottom_left_corner_.y);
    glm::vec2 lower_left_corner(
        div_idx * width_unit, bottom_left_corner_.y);

    ci::Path2d key;
    key.moveTo(upper_left_corner);
    key.lineTo(upper_right_corner);
    key.lineTo(lower_right_corner);
    key.lineTo(lower_left_corner);
    key.close();

    if (should_draw) {
      ci::gl::draw(key);
    }

    keys_.push_back(key);
  }
}

}

}