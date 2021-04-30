// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <cstdlib>
#include "cinder/gl/gl.h"
#include <cinder/Path2d.h>
#include <cinder/Shape2d.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

namespace scalepiegraph {

namespace frontend {

/**
 * A class representing a Pie Graph with resizable proportions.
 */
class PieGraph {
 public:
  /**
   * Construct a pie graph with default parameters. Cannot be drawn.
   */
  PieGraph() = default;

  /**
   * Construct a Pie Graph centered in the specified location with the specified
   * radius and proportions.
   *
   * @param pos The position of the pie graph
   * @param radius The radius of the pie graph
   * @param proportions The proportions of the pie graph as a vector of floats
   * in the range 0, inclusive to 1, inclusive.
   */
  PieGraph(const glm::vec2& pos, float radius, std::vector<float> proportions);

  /**
   * Draw this Pie Graph.
   */
  void Draw();

  /**
   * Get the index of the Handle nearest the specified position.
   *
   * @param pos The position which a handle must encompass
   * @return The index of the encompassing handle; -1 if there is none
   */
  int GetHandleIndex(const glm::vec2& pos) const;

  /**
   * Update the proportion delimited by a handle with the specified index by
   * changing its angular position on the Pie Graph's arc. This new position
   * is calculated by the angle between the mouse position vector relative
   * to the center of the Pie Graph and the apex of the Pie Graph.
   *
   * @param handle_index The index of the handle to update
   * @param mouse_pos The position used to calculate the new angle
   * @return True if the update was successful; otherwise, false
   */
  bool UpdateHandle(size_t handle_index, glm::vec2 mouse_pos);

  /**
   * Get the position of this Pie Graph.
   *
   * @return The position of this Pie Graph
   */
  glm::vec2 GetCenter() const;

  /**
   * Get the radius of this Pie Graph.
   *
   * @return The radius of this Pie Graph
   */
  float GetRadius() const;

  /**
   * Get the current proportions of this Pie Graph.
   *
   * @return The proportions of this Pie Graph.
   */
  std::vector<float> GetProportions() const;

 private:
  static const float kCircleStartOffset;
  static const float kHandleRadius;
  static const ci::Color kStrokeColor;

  /**
   * Create the handles for this Pie Graph and optionally draw them.
   *
   * @param should_draw Whether the handles should be drawn.
   */
  void CreateHandles(bool should_draw=true);

  ci::Path2d current_arc_;
  std::vector<ci::Path2d> current_handles_;
  glm::vec2 center_;
  float radius_;
  std::vector<float> division_radians_;
};

} // namespace frontend

} // namespace scalepiegraph