// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <cinder/gl/gl.h>

namespace scalepiegraph {

namespace frontend {

class Keyboard {
 public:
  Keyboard() = default;

  Keyboard(const glm::vec2& bottom_left_corner,
           float width,
           float height,
           size_t num_divisions);

  void Draw();

  void UpdateDivisions(size_t num_divisions);

 private:
  glm::vec2 bottom_left_corner_;
  float width_;
  float height_;
  size_t current_divisions_;
};

}

}