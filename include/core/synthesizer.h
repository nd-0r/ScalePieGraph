// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <cinder/audio/Node.h>
#include <cinder/audio/GenNode.h>
#include <cinder/audio/WaveformType.h>
#include <cinder/audio/Context.h>
#include <cinder/audio/GainNode.h>
#include <cinder/audio/FilterNode.h>
#include <cinder/audio/InputNode.h>
#include <cinder/audio/NodeEffects.h>

namespace scalepiegraph {

class Synthesizer {
 public:
  Synthesizer();

  void Play(double frequency) const;

  void Stop() const;

  void SetWaveform(cinder::audio::WaveformType waveform_type) const;

  void SetGain(float gain);

  void SetFilter(float cutoff);

  // TODO - Implement
  void SetEnvelope(float attack, float delay, float sustain, float release);
 private:
  const double kFrequencyMax = 20000;
  const double kFrequencyMin = 20;

  ci::audio::Context* context_;
  ci::audio::GenOscNodeRef oscillator_;
  ci::audio::FilterLowPassNodeRef filter_;
  ci::audio::GainNodeRef gain_;
  float frequency_ = 440;
};

}