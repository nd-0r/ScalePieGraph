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

// void mouseDown(ci::app::MouseEvent event);

//void mouseDrag(ci::app::MouseEvent event);
//
//void keyDown(ci::app::KeyEvent event);
//
//void fileDrop(ci::app::FileDropEvent event);

}

}