// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/pie_graph.h>

namespace scalepiegraph {

namespace frontend {

const float PieGraph::kCircleStartOffset = 0.5 * glm::pi<float>();
const float PieGraph::kHandleRadius = 5;
const ci::Color PieGraph::kStrokeColor = ci::Color("white");

PieGraph::PieGraph(
    const glm::vec2& pos, float radius, std::vector<float> proportions) :
    center_(pos), radius_(radius) {
  for (float proportion : proportions) {
    // Convert proportions to radians
    division_radians_.push_back(proportion * 2 * glm::pi<float>());
  }

  CreateHandles(false);
}

void PieGraph::Draw() {
  ci::Path2d outer_arc;
  ci::Path2d end_caps;

  float arc_end = division_radians_.back() + kCircleStartOffset;
  outer_arc.arc(center_, radius_, kCircleStartOffset, -arc_end, false);
  outer_arc.lineTo(center_);

  glm::vec2 start(center_.x, center_.y - radius_);
  end_caps.moveTo(center_);
  end_caps.lineTo(start);

  ci::gl::color(kStrokeColor);
  ci::gl::draw(outer_arc);
  ci::gl::draw(end_caps);

  current_arc_ = outer_arc;

  CreateHandles(true);
}

int PieGraph::GetHandleIndex(const glm::vec2& pos) const {
  int handle_idx = 0;

  for (const ci::Path2d& handle : current_handles_) {
    if (handle.contains(pos)) {
      return handle_idx;
    }

    ++handle_idx;
  }

  return -1; // Position is not inside a handle
}

std::vector<float> PieGraph::GetProportions() const {
  std::vector<float> proportions;

  for (float radian : division_radians_) {
    // Convert to normalized proportions
    proportions.push_back(radian / (2 * glm::pi<float>()));
  }

  return proportions;
}

// TODO - remove
glm::vec2 PieGraph::CalcClosestPointOnArc(const glm::vec2& point) const {
  std::vector<glm::vec2> points = current_arc_.subdivide();

  float min_dist = std::numeric_limits<float>::max();
  glm::vec2 closest_point;

  for (const glm::vec2& arc_point : points) {
    float dist = glm::distance(arc_point, point);
    if (dist < min_dist) {
      closest_point = arc_point;
      min_dist = dist;
    }
  }

  return closest_point;
}

void PieGraph::CreateHandles(bool should_draw) {
  current_handles_ = std::vector<ci::Path2d>();

  glm::vec2 rad_vec = glm::vec2(center_.x, center_.y - radius_) - center_;

  for (float sweep : division_radians_) {
    sweep += kCircleStartOffset;

    float new_x = glm::cos(sweep) * rad_vec.x + glm::sin(sweep) * rad_vec.y;
    float new_y = -glm::sin(sweep) * rad_vec.x + glm::cos(sweep) * rad_vec.y;
    glm::vec2 handle_point = glm::vec2(new_x + center_.x, new_y + center_.y);

    ci::Path2d handle;
    handle.arc(handle_point, kHandleRadius, 0, 2 * glm::pi<float>());
    handle.close();
    current_handles_.push_back(handle);

    if (should_draw) {
      ci::gl::color(kStrokeColor);
      ci::gl::drawLine(center_, handle_point);
      ci::gl::drawSolid(handle);
    }
  }
}

} // namespace frontend

} // namespace scalepiegraph