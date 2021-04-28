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
  last_mouse_down_pos = event.getPos();
  std::cout << last_mouse_down_pos << std::endl;
}

void ScalePieGraphApp::mouseUp(ci::app::MouseEvent event) {
  float window_x_pos = event.getWindow()->getPos().x;
  float window_y_pos = event.getWindow()->getPos().y;
  glm::vec2 mouse_pos = glm::vec2(
      event.getPos().x - window_x_pos, event.getPos().y - window_y_pos);
  std::cout << mouse_pos << std::endl;

  if (glm::distance(mouse_pos, last_mouse_down_pos) > 1) {
    int handle_idx = graph_.GetHandleIndex(event.getPos());
    std::cout << handle_idx << std::endl;
    if (graph_.UpdateHandle(handle_idx, mouse_pos)) {
      std::cout << "good" << std::endl;
    }
    std::cout << "bad" << std::endl;
  }
}
// TODO - fix
/*void ScalePieGraphApp::mouseDrag(ci::app::MouseEvent event) {
  glm::vec2 mouse_pos = event.getPos();

  if (glm::distance(mouse_pos, last_mouse_down_pos) > 1) {
    int handle_idx = graph_.GetHandleIndex(mouse_pos);
    if (graph_.UpdateHandle(handle_idx, mouse_pos)) {
      std::cout << "good" << std::endl;
    }
  }
}*/

// TODO - implement
//void keyDown(ci::app::KeyEvent event);
//
//void fileDrop(ci::app::FileDropEvent event);

}

}