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

} // namespace frontend

} // namespace scalepiegraph