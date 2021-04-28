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

  int GetHandleIndex(const glm::vec2& pos) const;

  bool UpdateHandle(size_t handle_index, const glm::vec2& new_pos);

  std::vector<float> GetProportions() const;

 private:
  static const float kCircleStartOffset;
  static const float kHandleRadius;
  static const ci::Color kStrokeColor;

  glm::vec2 CalcClosestPointOnArc(const glm::vec2& point) const;
  void CreateHandles(bool should_draw=true);

  ci::Path2d current_arc_;
  std::vector<ci::Path2d> current_handles_;

  glm::vec2 center_;
  float radius_;
  std::vector<float> division_radians_;
};

}

}