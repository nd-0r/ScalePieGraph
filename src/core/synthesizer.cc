// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/synthesizer.h>

namespace scalepiegraph {

Synthesizer::Synthesizer() : context_(ci::audio::Context::master()) {
  if (context_ == nullptr) {
    throw std::runtime_error("No audio device found");
  }

  oscillator_ = context_->makeNode(
      new ci::audio::GenOscNode(ci::audio::WaveformType::SINE, frequency_));
  filter_ = context_->makeNode(new ci::audio::FilterLowPassNode);
  gain_ = context_->makeNode(new ci::audio::GainNode);

  oscillator_->connect(filter_);
  filter_->connect(gain_);
  gain_->connect(context_->getOutput());

  oscillator_->enable();
  filter_->enable();
  gain_->enable();
}



}
