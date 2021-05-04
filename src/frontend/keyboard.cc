// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/keyboard.h>

namespace scalepiegraph {

namespace frontend {

const ci::Color Keyboard::kStrokeColor = ci::Color("white");
const ci::Color Keyboard::kKeyColor = ci::Color("black");
const ci::Color Keyboard::kOctaveShade = ci::Color("grey");

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

  for (size_t div_idx = 0;
       div_idx < current_divisions_ * num_octaves_;
       ++div_idx) {
    float width_unit = width_ / (current_divisions_ * num_octaves_);

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
      if (div_idx % (current_divisions_ - 1) == 0) {
        ci::gl::color(kOctaveShade);
        ci::gl::drawSolid(key);
      } else {
        ci::gl::color(kKeyColor);
        ci::gl::drawSolid(key);
      }

      ci::gl::color(kStrokeColor);
      ci::gl::draw(key);
    }

    keys_.push_back(key);
  }
}

void Keyboard::SetNumOctaves(size_t num_octaves) {
  num_octaves_ = num_octaves;
}

size_t Keyboard::GetNumOctaves() const {
  return num_octaves_;
}

}

}