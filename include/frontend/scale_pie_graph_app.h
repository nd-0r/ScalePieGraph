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

//  void mouseDown(ci::app::MouseEvent event) override;
//  // Store previous pie graph so that it can be reverted if not a valid scale
//
//  void mouseDrag(ci::app::MouseEvent event) override;
//
//  void keyDown(ci::app::KeyEvent event) override;
//
//  void fileDrop(ci::app::FileDropEvent event) override;

  const double kDefaultWindowSize = 600;
  const double kDefaultMargin = 20;

 private:
  // const float kGoldMean = 1.6180339887; // ratio of window to pie graph center
  // bool is_ready_ = false; // App is not ready until the dataset is loaded
  double current_width_;
  double current_height_;
  ScaleDataset scale_dataset_;
  Scale current_scale_;
  PieGraph graph_;
  Keyboard keyboard_;

  const ci::Color kBackgroundColor = ci::Color("black");
};

}  // namespace frontend

}  // namespace scalepiegraph