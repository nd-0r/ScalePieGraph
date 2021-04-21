// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/scale.h>

namespace scalepiegraph {

Scale::Scale(const std::string& name, const std::vector<float>& intervals) :
    name_(name), intervals_(std::vector<float>(intervals.size())) {
  if (intervals.size() == 0) {
    throw std::out_of_range("Scale must have at least one interval!");
  }

  if (intervals.size() > kCentsInOctave) {
    throw std::out_of_range("Intervals must be wider than one cent.");
  }

  float current_span = 0;
  for (size_t inter_index = 0; inter_index < intervals.size(); ++inter_index) {
    current_span += intervals[inter_index];

    if (current_span > kCentsInOctave || intervals[inter_index] < 1) {
      throw std::out_of_range("Invalid intervals.");
    }

    intervals_[inter_index] = current_span;
  }
}

Scale::Scale(size_t num_divisions) {
  if (num_divisions == 0) {
    throw std::out_of_range("Scale must have at least one interval!");
  }

  if (num_divisions > kCentsInOctave) {
    throw std::out_of_range("Intervals must be wider than one cent.");
  }

  name_ = "Chromatic Scale " + std::to_string(num_divisions) + " TET";
  intervals_ = std::vector<float>(num_divisions);

  float inter_size = kCentsInOctave / num_divisions;
  float current_span = 0;
  for (size_t inter_index = 0; inter_index < num_divisions; ++inter_index) {
    current_span += inter_size;

    intervals_[inter_index] = current_span;
  }
}

void Scale::UpdateIntervalSize(size_t inter_index, float percent_change) {
  if (inter_index > intervals_.size()) {
    throw std::out_of_range("Scale index exceeds size of scale.");
  }

  float change;
  float interval;
  if (inter_index == 0) {
    interval = intervals_[0];
    change = percent_change * interval - interval;
  } else {
    interval = intervals_[inter_index] - intervals_[inter_index - 1];
    change = percent_change * interval - interval;
  }

  if (interval + change < 1) {
    throw std::runtime_error("New interval too small!");
  }

  for (size_t index = inter_index; index < intervals_.size(); ++index) {
    float modified_inter = intervals_[index] + change;

    if (modified_inter > kCentsInOctave) {
      throw std::out_of_range("Scale exceeds octave!");
    }

    intervals_[index] = modified_inter;
  }
}

double Scale::CalculateNoteFrequency(float base_freq, size_t note_index) const {
  if (base_freq < 0) {
    throw std::out_of_range("Base frequency must be a positive real number");
  }

  if (note_index == 0) {
    return base_freq;
  }

  if (note_index > intervals_.size() - 1) {
    throw std::out_of_range("Invalid interval index for this scale!");
  }

  double freq =
      base_freq * std::pow(2, (intervals_[note_index - 1] / kCentsInOctave));

  return freq;
}

float Scale::GetInterval(size_t inter_index) const {
  if (inter_index > intervals_.size()) {
    throw std::out_of_range("Invalid interval index for this scale!");
  }

  if (inter_index == 0) {
    return intervals_[inter_index];
  }

  return intervals_[inter_index] - intervals_[inter_index - 1];
}

size_t Scale::GetNumIntervals() const {
  return intervals_.size();
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

