// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <frontend/scale_pie_graph_app.h>

namespace scalepiegraph {

namespace frontend {

ScalePieGraphApp::ScalePieGraphApp() :
    current_width_(kMinWindowSize),
    current_height_(kMinWindowSize),
    current_scale_(Scale(12)) { // Load a default 12 TET scale
  ci::app::setWindowSize(current_width_, current_height_);

  UpdateText("Drop scale dataset to begin");

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

  ci::gl::draw(text_box_texture_,
               glm::vec2(2 * current_width_ / 3, current_height_ / 4));
}

void ScalePieGraphApp::mouseDown(ci::app::MouseEvent event) {
  if (is_ready_) {
    last_graph_ = graph_;
    current_handle_idx_ = graph_.GetHandleIndex(event.getPos());
    std::cout << current_handle_idx_ << std::endl;
    last_mouse_down_pos_ = event.getPos();

    int key_idx = keyboard_.GetKeyIndex(event.getPos());
    if (key_idx >= 0) {
      StartSynthesizer(key_idx);
    }
  }
}

void ScalePieGraphApp::mouseUp(ci::app::MouseEvent event) {
  if (is_ready_) {
    if (current_handle_idx_ >= 0) { // Handle selected
      try {
        current_scale_ = Scale("Custom",
                               graph_.GetProportions(),
                               current_scale_.GetNumOctaves());
        UpdateText();
      } catch (std::out_of_range&) {
        graph_ = last_graph_; // Revert to previous state
      }

      current_handle_idx_ = -1; // Handle deselected
    }

    synthesizer_.Stop();
  }
}

void ScalePieGraphApp::mouseDrag(ci::app::MouseEvent event) {
  if (is_ready_) {
    glm::vec2 mouse_pos(event.getPos());

    if ((glm::distance2(mouse_pos, last_mouse_down_pos_) > 1) &&
        current_handle_idx_ >= 0) {
      graph_.UpdateHandle(current_handle_idx_, mouse_pos);
    }

    int key_idx = keyboard_.GetKeyIndex(event.getPos());
    if (key_idx >= 0) {
      synthesizer_.SetFrequency(current_scale_.CalculateNoteFrequency(
          key_idx, base_scale_.CalculateNoteFrequency(current_transposition_)));
    }
  }
}

void ScalePieGraphApp::keyDown(ci::app::KeyEvent event) {
  if (is_ready_) {
    UpdateWaveform(event);
    HandleKeyboardNotes(event);
    HandleTransposition(event);
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_RIGHT:
        if (current_scale_idx_ == scale_names_.size() - 1) {
          break;
        }
        UpdateScale(scale_names_[current_scale_idx_++]);
        break;
      case ci::app::KeyEvent::KEY_LEFT:
        if (current_scale_idx_ == 0) {
          break;
        }
        UpdateScale(scale_names_[current_scale_idx_--]);
        break;
      case ci::app::KeyEvent::KEY_EQUALS:
        if (keyboard_.GetNumOctaves() == kMaxOctaves) {
          break;
        }
        keyboard_.SetNumOctaves(keyboard_.GetNumOctaves() + 1);
        break;
      case ci::app::KeyEvent::KEY_KP_MINUS:
        if (keyboard_.GetNumOctaves() == 1) {
          break; // Cannot have less than one octave
        }
        keyboard_.SetNumOctaves(keyboard_.GetNumOctaves() - 1);
        break;
    }
  }
}

void ScalePieGraphApp::StartSynthesizer(size_t note_idx) {
  synthesizer_.Start(current_scale_.CalculateNoteFrequency(
      note_idx, base_scale_.CalculateNoteFrequency(current_transposition_)));
}

void ScalePieGraphApp::UpdateWaveform(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_q:
      synthesizer_.SetWaveform(ci::audio::WaveformType::SINE);
      break;
    case ci::app::KeyEvent::KEY_w:
      synthesizer_.SetWaveform(ci::audio::WaveformType::TRIANGLE);
      break;
    case ci::app::KeyEvent::KEY_e:
      synthesizer_.SetWaveform(ci::audio::WaveformType::SQUARE);
      break;
    case ci::app::KeyEvent::KEY_r:
      synthesizer_.SetWaveform(ci::audio::WaveformType::SAWTOOTH);
      break;
  }
}

void ScalePieGraphApp::HandleKeyboardNotes(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_a:
      StartSynthesizer(0);
      break;
    case ci::app::KeyEvent::KEY_s:
      StartSynthesizer(1);
      break;
    case ci::app::KeyEvent::KEY_d:
      StartSynthesizer(2);
      break;
    case ci::app::KeyEvent::KEY_f:
      StartSynthesizer(3);
      break;
    case ci::app::KeyEvent::KEY_g:
      StartSynthesizer(4);
      break;
    case ci::app::KeyEvent::KEY_h:
      StartSynthesizer(5);
      break;
    case ci::app::KeyEvent::KEY_j:
      StartSynthesizer(6);
      break;
    case ci::app::KeyEvent::KEY_k:
      StartSynthesizer(7);
      break;
    case ci::app::KeyEvent::KEY_l:
      StartSynthesizer(8);
      break;
    case ci::app::KeyEvent::KEY_SEMICOLON:
      StartSynthesizer(9);
      break;
    case ci::app::KeyEvent::KEY_QUOTE:
      StartSynthesizer(10);
      break;
    case ci::app::KeyEvent::KEY_SPACE:
      synthesizer_.Stop();
      break;
  }
}

void ScalePieGraphApp::HandleTransposition(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_UP:
      if (current_transposition_ == base_scale_.GetNumNotes()) {
        break; // No more notes in the base scale
      }
      ++current_transposition_;
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      if (current_transposition_ == 0) {
        break; // No less notes in the base scale
      }
      --current_transposition_;
      break;
  }
}

void ScalePieGraphApp::fileDrop(ci::app::FileDropEvent event) {
  std::ifstream scale_dataset_file;
  scale_dataset_file.open(event.getFile(0).string());

  try {
    scale_dataset_file >> scale_dataset_;
    scale_names_ = scale_dataset_.GetNames();
    UpdateScale(scale_names_.front());
    is_ready_ = true;
  } catch (std::runtime_error&) {
    UpdateText("Invalid File");
  }

  scale_dataset_file.close();
}

void ScalePieGraphApp::UpdateScale(const std::string& new_scale_name) {
  current_scale_ = scale_dataset_[new_scale_name];
  graph_ = PieGraph(
      graph_.GetCenter(),
      graph_.GetRadius(),
      current_scale_.GetProportions());
  UpdateText();

  keyboard_.UpdateDivisions(current_scale_.GetNumNotes() + 1);
}

void ScalePieGraphApp::UpdateText(const std::string& custom_text) {
  if (custom_text.empty()) {
    title_ = current_scale_.GetName();;
    info_ = current_scale_.GetDescription();
  } else {
    title_ = custom_text;
    info_ = "";
  }

  ci::TextBox text_box = ci::TextBox().alignment(ci::TextBox::LEFT).size(
      glm::vec2((current_width_ - kMargin) / 3.0, ci::TextBox::GROW));

  text_box.text(info_).color(ci::Color("white"));

  text_box_texture_ = ci::gl::Texture2d::create(text_box.render());
}

} // namespace frontend

} // namespace scalepiegraph