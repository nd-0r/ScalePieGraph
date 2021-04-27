// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/pie_graph.h>

namespace scalepiegraph {

namespace frontend {

const float PieGraph::kCircleStartOffset = 0.5 * glm::pi<float>();
const float PieGraph::kHandleRadius = 5;
const ci::Color PieGraph::kStrokeColor = ci::Color("white");

PieGraph::PieGraph(
    const glm::vec2& pos, float radius, std::vector<float> proportions) :
      center_(pos), radius_(radius), proportions_(proportions) {}

void PieGraph::Draw() {
  ci::Path2d outer_arc;
  ci::Path2d end_caps;

  float arc_end =
      proportions_.back() * 2 * glm::pi<float>() + kCircleStartOffset;
  outer_arc.arc(center_, radius_, kCircleStartOffset, -arc_end, false);
  outer_arc.lineTo(center_);

  glm::vec2 start(center_.x, center_.y - radius_);
  end_caps.moveTo(center_);
  end_caps.lineTo(start);

  ci::gl::color(kStrokeColor);
  ci::gl::draw(outer_arc);
  ci::gl::draw(end_caps);

  glm::vec2 rad_vec = start - center_;
  for (float proportion : proportions_) {
    float sweep = 2 * glm::pi<float>() * proportion;

    float new_x = glm::cos(sweep) * rad_vec.x + glm::sin(sweep) * rad_vec.y;
    float new_y = -glm::sin(sweep) * rad_vec.x + glm::cos(sweep) * rad_vec.y;
    glm::vec2 handle_point = glm::vec2(new_x + center_.x, new_y + center_.y);

    ci::gl::color(kStrokeColor);
    ci::gl::drawLine(center_, handle_point);
    ci::gl::drawSolidCircle(handle_point, kHandleRadius);
  }
}

/*size_t PieGraph::GetNearestHandleIndex(const glm::vec2& pos) const;

void PieGraph::UpdateHandle(size_t handle_index, glm::vec2& new_pos);

std::vector<float> PieGraph::GetProportions() const;*/

}

}