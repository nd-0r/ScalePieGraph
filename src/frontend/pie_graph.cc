// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/pie_graph.h>

namespace scalepiegraph {

namespace frontend {

const float PieGraph::kCircleStartOffset = 1.5 * glm::pi<float>();
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
  outer_arc.arc(center_, -radius_, -kCircleStartOffset, -arc_end, false);
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

bool PieGraph::UpdateHandle(size_t handle_index, glm::vec2 mouse_pos) {
  float curr_angle = division_radians_[handle_index];
  glm::vec2 mouse_vec(mouse_pos - center_);
  glm::vec2 rad_vec(0, -radius_);
  glm::vec2 rad_vec_left_normal(-radius_, 0);

  float new_handle_angle = glm::acos(glm::dot(rad_vec, mouse_vec) /
      (glm::length(mouse_vec) * glm::length(rad_vec)));

  if (glm::dot(mouse_vec, rad_vec_left_normal) < 0) {
    new_handle_angle = 2 * glm::pi<float>() - new_handle_angle;
  }

  if ((handle_index == 0 && new_handle_angle < 0) ||
      new_handle_angle <= division_radians_[handle_index - 1]) {
    return false; // Cannot make section less than 0 radians wide
  }

  float diff = new_handle_angle - curr_angle;

  if ((handle_index == division_radians_.size() - 1 &&
       new_handle_angle > 2 * glm::pi<float>()) ||
      division_radians_.back() + diff > 2 * glm::pi<float>()) {
    return false; // New size causes pie graph to exceed 2 Pi radians
  }

  for (size_t current_handle_idx = handle_index;
       current_handle_idx < division_radians_.size();
       ++current_handle_idx) {
    division_radians_[current_handle_idx] += diff;
  }

  return true; // Portion successfully resized
}

std::vector<float> PieGraph::GetProportions() const {
  std::vector<float> proportions;

  for (float radian : division_radians_) {
    // Convert to normalized proportions
    proportions.push_back(radian / (2 * glm::pi<float>()));
  }

  return proportions;
}

void PieGraph::CreateHandles(bool should_draw) {
  current_handles_ = std::vector<ci::Path2d>();

  glm::vec2 rad_vec = glm::vec2(0, -radius_);

  size_t current_idx = 0;
  for (float sweep : division_radians_) {
    float new_x = glm::cos(sweep) * rad_vec.x + glm::sin(sweep) * rad_vec.y;
    float new_y = -glm::sin(sweep) * rad_vec.x + glm::cos(sweep) * rad_vec.y;
    glm::vec2 handle_point = glm::vec2(new_x + center_.x, new_y + center_.y);

    // If handles overlap
    if (current_idx > 0 &&
         current_handles_[current_idx - 1].contains(handle_point)) {
      float x_buffer = 4 * glm::cos(sweep + kCircleStartOffset) * kHandleRadius;
      float y_buffer = 4 * glm::sin(sweep + kCircleStartOffset) * kHandleRadius;
      handle_point =
          glm::vec2(handle_point.x - x_buffer, handle_point.y + y_buffer);
    }

    ci::Path2d handle;
    handle.arc(handle_point, kHandleRadius, 0, 2 * glm::pi<float>());
    handle.close();
    current_handles_.push_back(handle);

    if (should_draw) {
      ci::gl::color(kStrokeColor);
      ci::gl::drawLine(center_, handle_point);
      ci::gl::drawSolid(handle);
    }

    ++current_idx;
  }
}

} // namespace frontend

} // namespace scalepiegraph