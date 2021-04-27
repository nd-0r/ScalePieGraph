// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <cstdlib>
#include <glm/detail/type_vec2.hpp>
#include <glm/vec2.hpp>
#include <cinder/Path2d.h>
#include <cinder/Shape2d.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

namespace scalepiegraph {

namespace frontend {

class PieGraph {
 public:
  PieGraph() = default;

  PieGraph(const glm::vec2& pos, float radius, std::vector<float> proportions);

  void Draw();

  size_t GetNearestHandleIndex(const glm::vec2& pos) const;

  void UpdateHandle(size_t handle_index, glm::vec2& new_pos);

  std::vector<float> GetProportions() const;

 private:
  static const float kCircleStartOffset;
  static const float kHandleRadius;
  static const ci::Color kStrokeColor;

  glm::vec2 center_;
  float radius_;
  std::vector<float> proportions_;
  std::vector<glm::vec2> handles_;
};

}

}