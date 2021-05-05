// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <cinder/audio/Node.h>
#include <cinder/audio/GenNode.h>
#include <cinder/audio/WaveformType.h>
#include <cinder/audio/Context.h>
#include <cinder/audio/GainNode.h>
#include <cinder/audio/FilterNode.h>

namespace scalepiegraph {

/**
 * A class representing a sound synthesizer with variable waveform, gain, and
 * filter.
 */
class Synthesizer {
 public:
  /**
   * Create a Synthesizer by initializing the audio context and patching the
   * required effect and generator nodes.
   */
  Synthesizer();

  /**
   * Start this Synthesizer or do nothing if Synthesizer is already started.
   *
   * @param frequency The frequency at which to start this Synthesizer.
   */
  void Start(double frequency) const;

  /**
   * Stop this Synthesizer or do nothing if Synthesizer is already stopped.
   */
  void Stop() const;

  /**
   * Set the frequency of this Synthesizer.
   *
   * @param frequency The frequency to which to set this Synthesizer
   */
  void SetFrequency(double frequency) const;

  /**
   * Set the waveform of this Synthesizer.
   *
   * @param waveform_type The waveform type to which to set this Synthesizer
   */
  void SetWaveform(ci::audio::WaveformType waveform_type) const;

  /**
   * Set the cutoff frequency of this Synthesizer's filter.
   *
   * @param cutoff The cutoff at which to set this Synthesizer's filter
   */
  void SetFilter(float cutoff);
 private:
  const double kFrequencyMax = 20000;
  const double kFrequencyMin = 20;

  ci::audio::Context* context_;
  ci::audio::GenOscNodeRef oscillator_;
  ci::audio::FilterLowPassNodeRef filter_;
  ci::audio::GainNodeRef gain_;
};

} // namespace scalepiegraph