#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
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

  // void mouseUp(ci::app::MouseEvent event) override;

  // TODO
  // Store previous pie graph so that it can be reverted if not a valid scale

  void mouseDrag(ci::app::MouseEvent event) override;
//
//  void keyDown(ci::app::KeyEvent event) override;
//
//  void fileDrop(ci::app::FileDropEvent event) override;

  const double kDefaultWindowSize = 600;
  const double kDefaultMargin = 20;

 private:
  // TODO bool is_ready_ = false; // App is not ready until the dataset is loaded
  const ci::Color kBackgroundColor = ci::Color("black");
  double current_width_;
  double current_height_;
  std::string title_;
  std::string info_;
  glm::vec2 last_mouse_down_pos_;
  int current_handle_idx_ = -1;

  ScaleDataset scale_dataset_;
  Scale current_scale_;

  PieGraph graph_;
  Keyboard keyboard_;
};

}  // namespace frontend

}  // namespace scalepiegraph