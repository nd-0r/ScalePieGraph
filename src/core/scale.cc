// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/scale.h>

namespace scalepiegraph {

Scale::Scale(const std::string& name, const std::vector<float>& intervals) :
    name_(name) {
  if (intervals.size() == 0) {
    throw std::out_of_range("Scale must have at least one interval!");
  }

  if (intervals.size() > kCentsInOctave) {
    throw std::out_of_range("Intervals must be wider than one cent.");
  }

  float span = 0;
  for (float inter : intervals) {
    span += inter;

    if (span > kCentsInOctave || inter < 1) {
      throw std::out_of_range("Invalid intervals.");
    }
  }

  intervals_ = intervals;
}

Scale::Scale(size_t num_divisions) {
  if (num_divisions == 0) {
    throw std::out_of_range("Scale must have at least one interval!");
  }

  if (num_divisions > kCentsInOctave) {
    throw std::out_of_range("Intervals must be wider than one cent.");
  }

  name_ = "Chromatic Scale " + std::to_string(num_divisions) + " TET";
  intervals_ =
      std::vector<float>(num_divisions, kCentsInOctave / num_divisions);
}

void Scale::UpdateIntervalSize(size_t inter_index, float percent_change) {
  if (inter_index > intervals_.size()) {
    throw std::out_of_range("Scale index exceeds size of scale.");
  }

  float modified_inter = intervals_[inter_index] * percent_change;
  if (modified_inter < 1) {
    throw std::runtime_error("New interval too small!");
  }

  float scale_span = 0;
  for (size_t index = 0; index < intervals_.size(); ++index) {
    if (index == inter_index) {
      scale_span += modified_inter;
      continue;
    }

    scale_span += intervals_[index];
  }

  if (scale_span > kCentsInOctave) {
    throw std::out_of_range("Scale exceeds octave!");
  }

  intervals_[inter_index] = modified_inter;
}

double Scale::CalculateNoteFrequency(float base_freq, size_t note_index) const {
  if (note_index == 0) {
    return base_freq;
  }

  if (note_index - 1 > intervals_.size()) {
    throw std::out_of_range("Invalid interval index for this scale!");
  }

  double freq =
      base_freq * std::pow(2, (intervals_[note_index - 1] / kCentsInOctave));

  if (freq > kFrequencyMax || freq < kFrequencyMin) {
    throw std::out_of_range("Note frequency out of range.");
  }

  return freq;
}

float Scale::GetInterval(size_t inter_index) const {
  if (inter_index > intervals_.size()) {
    throw std::out_of_range("Invalid interval index for this scale!");
  }

  return intervals_[inter_index];
}

size_t Scale::GetNumIntervals() const {
  return intervals_.size();
}

size_t Scale::GetNumNotes() const {
  return intervals_.size() + 1;
}

const std::string& Scale::GetName() const {
  return name_;
}

// TODO - implement instream and ostream operator overloads

bool Scale::operator==(const Scale &other_scale) const {
  if (name_ != other_scale.name_ ||
      intervals_.size() != other_scale.intervals_.size()) {
    return false;
  }

  return intervals_ == other_scale.intervals_;
}

bool Scale::operator!=(const Scale &other_scale) const {
  return !operator==(other_scale);
}


}

