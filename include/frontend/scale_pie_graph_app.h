// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/params/Params.h"
#include <core/scale_dataset.h>
#include <core/synthesizer.h>
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
  const ci::Color kBackgroundColor = ci::Color("black");
  const ci::Color kTextColor = ci::Color("white");
  const size_t kMaxOctaves = 4;

  /**
   * Start the synthesizer at the specified note index using the current scale.
   *
   * @param note_idx The note index at which to start the synthesizer
   */
  void StartSynthesizer(size_t note_idx);

  /**
   * Update the waveform of the synthesizer given a specified keyboard input.
   *
   * @param event The keyboard event to trigger the new waveform
   */
  void UpdateWaveform(ci::app::KeyEvent event);

  /**
   * Translate keyboard events to note inputs to the synthesizer.
   *
   * @param event The keyboard event to trigger the synthesizer
   */
  void HandleKeyboardNotes(ci::app::KeyEvent event);

  /**
   * Translate keyboard events into transposition commands.
   *
   * @param event The keyboard event to trigger a transposition command
   */
  void HandleTransposition(ci::app::KeyEvent event);

  /**
   * Update the current scale to a scale with the specified name in the dataset.
   *
   * @param new_scale_name The name of the new scale to load
   */
  void UpdateScale(const std::string& new_scale_name);

  /**
   * Update the text displayed onscreen. Optional custom text overrides text
   * from the scale, instead displaying the given text in place of the title,
   * and no text in the description.
   *
   * @param custom_text Optional overriding text; default is empty string
   */
  void UpdateText(const std::string& custom_text = "");

  bool is_ready_ = false; // App is not ready until the dataset is loaded
  double current_width_;
  double current_height_;
  std::string title_;
  std::string info_;
  glm::vec2 last_mouse_down_pos_;
  int current_handle_idx_ = -1;
  ScaleDataset scale_dataset_;
  std::vector<std::string> scale_names_;
  Scale base_scale_ = Scale(12); // Base scale to use for transposition
  size_t current_transposition_ = 0;
  Scale current_scale_;
  size_t current_scale_idx_ = 0;
  ci::gl::TextureRef text_box_texture_;
  PieGraph last_graph_;
  PieGraph graph_;
  Keyboard keyboard_;
  Synthesizer synthesizer_;
};

}  // namespace frontend

}  // namespace scalepiegraph