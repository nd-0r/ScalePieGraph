#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace scalepiegraph {

namespace frontend {

class ScalePieGraphApp : public ci::app::App {
 public:
  ScalePieGraphApp();

  void draw() override;

  void mouseDown(ci::app::MouseEvent event) override;

  void mouseDrag(ci::app::MouseEvent event) override;

  void keyDown(ci::app::KeyEvent event) override;

  void fileDrop(ci::app::FileDropEvent event) override;

  const double kWindowSize = 875;
  const double kMargin = 100;

 private:
};

}  // namespace visualizer

}  // namespace naivebayes