// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/scale_pie_graph_app.h>

namespace scalepiegraph {

namespace frontend {

ScalePieGraphApp::ScalePieGraphApp() :
    current_width_(kDefaultWindowSize),
    current_height_(kDefaultWindowSize),
    current_scale_(Scale(12)) {
  ci::app::setWindowSize(current_width_, current_height_);

  glm::vec2 graph_center(current_width_ / 2, current_height_ / 3);
  graph_ = PieGraph(graph_center,
                    graph_center.y - kDefaultMargin,
                    current_scale_.GetProportions());

  keyboard_ = Keyboard(glm::vec2(0, current_height_),
                       current_width_,
                       current_height_ / 3,
                       current_scale_.GetNumIntervals());

  scale_dataset_ = ScaleDataset();
}

void ScalePieGraphApp::draw() {
  ci::gl::clear(kBackgroundColor);
  graph_.Draw();
  keyboard_.Draw();
}

void ScalePieGraphApp::mouseDown(ci::app::MouseEvent event) {
  current_handle_idx_ = graph_.GetHandleIndex(event.getPos());
  std::cout << current_handle_idx_ << std::endl;
  last_mouse_down_pos_ = event.getPos();
}

void ScalePieGraphApp::mouseUp(ci::app::MouseEvent event) {
  current_handle_idx_ = -1; // Handle deselected
}

void ScalePieGraphApp::mouseDrag(ci::app::MouseEvent event) {
  glm::vec2 mouse_pos(event.getPos());

  if ((glm::distance2(mouse_pos, last_mouse_down_pos_) > 1) &&
      current_handle_idx_ >= 0) {
    if (!graph_.UpdateHandle(current_handle_idx_, mouse_pos)) {
      std::cout << "bad" << std::endl;
    }
  }
}

// TODO - implement
//void keyDown(ci::app::KeyEvent event);
//
//void fileDrop(ci::app::FileDropEvent event);

}

}