#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/params/Params.h"
#include <core/scale_dataset.h>
#include <frontend/pie_graph.h>
#include <frontend/keyboard.h>

namespace scalepiegraph {

namespace frontend {

class ScalePieGraphApp : public ci::app::App {
 public:
  ScalePieGraphApp();

  void draw() override;

  void mouseDown(ci::app::MouseEvent event) override;

  void mouseUp(ci::app::MouseEvent event) override;

  void mouseDrag(ci::app::MouseEvent event) override;

  void keyDown(ci::app::KeyEvent event) override;

  void fileDrop(ci::app::FileDropEvent event) override;

  const double kMinWindowSize = 800;
  const double kMargin = 100;

 private:
  void UpdateText(const std::string& custom_text = "");

  bool is_ready_ = false; // App is not ready until the dataset is loaded
  const ci::Color kBackgroundColor = ci::Color("black");
  double current_width_;
  double current_height_;
  std::string title_;
  std::string info_;
  glm::vec2 last_mouse_down_pos_;
  int current_handle_idx_ = -1;

  ScaleDataset scale_dataset_;
  std::vector<std::string> scale_names_;
  Scale current_scale_;

  // ci::params::InterfaceGlRef params_;

  ci::gl::TextureRef text_box_texture_;
  PieGraph last_graph_;
  PieGraph graph_;
  Keyboard keyboard_;
};

}  // namespace frontend

}  // namespace scalepiegraph