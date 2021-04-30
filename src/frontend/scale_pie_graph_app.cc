// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/scale_pie_graph_app.h>

namespace scalepiegraph {

namespace frontend {

ScalePieGraphApp::ScalePieGraphApp() :
    current_width_(kMinWindowSize),
    current_height_(kMinWindowSize),
    current_scale_(Scale(12)) { // Load a default 12 TET scale
  ci::app::setWindowSize(current_width_, current_height_);

  UpdateText();

  glm::vec2 graph_center(current_width_ / 3, current_height_ / 3);
  graph_ = PieGraph(graph_center,
                    graph_center.y - kMargin,
                    current_scale_.GetProportions());

  keyboard_ = Keyboard(glm::vec2(0, current_height_),
                       current_width_,
                       current_height_ / 3,
                       current_scale_.GetNumIntervals());
}

void ScalePieGraphApp::draw() {
  ci::gl::clear(kBackgroundColor);
  graph_.Draw();
  keyboard_.Draw();

  ci::gl::drawStringCentered(
      title_,
      glm::vec2(current_width_ / 2, kMargin / 2), ci::Color("white"));

  ci::gl::draw(text_box_texture_);
}

void ScalePieGraphApp::mouseDown(ci::app::MouseEvent event) {
  if (is_ready_) {
    current_handle_idx_ = graph_.GetHandleIndex(event.getPos());
    std::cout << current_handle_idx_ << std::endl;
    last_mouse_down_pos_ = event.getPos();
  }
}

void ScalePieGraphApp::mouseUp(ci::app::MouseEvent event) {
  if (is_ready_) {
    current_handle_idx_ = -1; // Handle deselected
  }
}

void ScalePieGraphApp::mouseDrag(ci::app::MouseEvent event) {
  if (is_ready_) {
    glm::vec2 mouse_pos(event.getPos());

    if ((glm::distance2(mouse_pos, last_mouse_down_pos_) > 1) &&
        current_handle_idx_ >= 0) {
      if (!graph_.UpdateHandle(current_handle_idx_, mouse_pos)) {
        std::cout << "bad" << std::endl;
      }
    }
  }
}

// TODO - implement
//void keyDown(ci::app::KeyEvent event);

void ScalePieGraphApp::fileDrop(ci::app::FileDropEvent event) {
  std::ifstream scale_dataset_file;
  scale_dataset_file.open(event.getFile(0).string());
  ScaleDataset dataset;

  try {
    scale_dataset_file >> dataset;
    scale_names_ = dataset.GetNames();
    current_scale_ = dataset[scale_names_.front()];
    UpdateText();
    is_ready_ = true;
  } catch (std::runtime_error&) {
    title_ = "Invalid file";
    info_ = "";
  }

  scale_dataset_file.close();
}

void ScalePieGraphApp::UpdateText() {
  title_ = current_scale_.GetName();
  info_ = current_scale_.GetDescription();

  ci::TextBox text_box = ci::TextBox().alignment(ci::TextBox::LEFT).size(
      glm::vec2(current_width_ / 3.0, ci::TextBox::GROW));

  text_box.text(info_).color(ci::Color("white"));

  text_box_texture_ = ci::gl::Texture2d::create(text_box.render());
}

}

}