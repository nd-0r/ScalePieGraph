// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/synthesizer.h>

namespace scalepiegraph {

Synthesizer::Synthesizer() : context_(ci::audio::Context::master()) {
  if (context_ == nullptr) {
    throw std::runtime_error("No audio device found");
  }

  oscillator_ = context_->makeNode(
      new ci::audio::GenOscNode(ci::audio::WaveformType::SINE));
  filter_ = context_->makeNode(new ci::audio::FilterLowPassNode);
  gain_ = context_->makeNode(new ci::audio::GainNode);

  oscillator_->connect(filter_);
  filter_->connect(gain_);
  gain_->connect(context_->getOutput());

  oscillator_->enable();
  filter_->enable();
  gain_->enable();
}

void Synthesizer::Start(double frequency) const {
  if (frequency < kFrequencyMin || frequency > kFrequencyMax) {
    throw std::range_error("Frequency out of synthesizer range.");
  }

  oscillator_->setFreq(frequency);

  context_->enable();
}

void Synthesizer::Stop() const {
  context_->disable();
}

void Synthesizer::SetWaveform(
    cinder::audio::WaveformType waveform_type) const {
  oscillator_->setWaveform(waveform_type);
}

void Synthesizer::SetGain(float gain) {
  gain_->setValue(gain);
}

void Synthesizer::SetFilter(float cutoff) {
  if (cutoff < kFrequencyMin || cutoff > kFrequencyMax) {
    throw std::runtime_error("Cutoff out of synthesizer range.");
  }

  filter_->setCutoffFreq(cutoff);
}

}
