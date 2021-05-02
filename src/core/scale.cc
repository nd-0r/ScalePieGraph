// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/scale.h>

namespace scalepiegraph {

const float Scale::kCentsInOctave = 1200.0;

Scale::Scale(const std::string& name,
             const std::vector<float>& intervals,
             const std::string& description,
             size_t num_octaves) :
    name_(name),
    description_(description),
    intervals_(std::vector<float>(intervals.size())),
    num_octaves_(num_octaves) {
  if (intervals.size() == 0) {
    throw std::out_of_range("Scale must have at least one interval!");
  }

  if (intervals.size() > num_octaves_ * kCentsInOctave) {
    throw std::out_of_range("Intervals must be wider than one cent.");
  }

  float current_span = 0;
  for (size_t inter_index = 0; inter_index < intervals.size(); ++inter_index) {
    current_span += intervals[inter_index];

    if (current_span > num_octaves_ * kCentsInOctave ||
        intervals[inter_index] < 1) {
      throw std::out_of_range("Invalid intervals.");
    }

    intervals_[inter_index] = current_span;
  }
}

Scale::Scale(const std::string& name,
             const std::vector<float>& proportions,
             size_t num_octaves) :
    Scale(name,
          ConvertProportionsToCents(proportions, num_octaves),
          "",
          num_octaves) {}

Scale::Scale(size_t num_divisions) {
  if (num_divisions == 0) {
    throw std::out_of_range("Scale must have at least one interval!");
  }

  if (num_divisions > num_octaves_ * kCentsInOctave) {
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

    if (modified_inter > num_octaves_ * kCentsInOctave) {
      throw std::out_of_range("Scale exceeds octave!");
    }

    intervals_[index] = modified_inter;
  }
}

void Scale::AppendInterval(float inter_size) {
  if (inter_size < 1) {
    throw std::runtime_error("New interval too small!");
  }

  if (intervals_.back() + inter_size > num_octaves_ * kCentsInOctave) {
    throw std::out_of_range("Scale exceeds octave!");
  }

  intervals_.push_back(intervals_.back() + inter_size);
}

void Scale::RemoveInterval() {
  if (intervals_.size() == 1) {
    throw std::out_of_range("Cannot remove interval from singleton scale");
  }

  intervals_.pop_back();
}

double Scale::CalculateNoteFrequency(size_t note_index, float base_freq) const {
  if (base_freq < 0) {
    throw std::out_of_range("Base frequency must be a positive real number");
  }

  if (note_index == 0) {
    return base_freq;
  }

  if (note_index > intervals_.size()) {
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

std::vector<float> Scale::GetProportions() const {
  std::vector<float> proportions;

  for (float interval : intervals_) {
    proportions.push_back(interval / (kCentsInOctave * num_octaves_));
  }

  return proportions;
}

const std::string& Scale::GetName() const {
  return name_;
}

const std::string& Scale::GetDescription() const {
  return description_;
}

size_t Scale::GetNumOctaves() const {
  return num_octaves_;
}

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

std::vector<float> Scale::ConvertProportionsToCents(
    const std::vector<float>& proportions, size_t num_octaves) {
  if (proportions.size() < 1) {
    throw std::out_of_range(
        "Provided proportions have less than one proportion");
  }

  std::vector<float> cents_intervals;

  float last_interval = 0;
  float total_cents = num_octaves * kCentsInOctave;
  for (float proportion : proportions) {
    if (proportion > 1 || proportion < 0) {
      throw std::out_of_range(
          "Proportions out of range 0, inclusive, to 1, inclusive.");
    }

    float current_interval = proportion * total_cents;
    cents_intervals.push_back(current_interval - last_interval);
    last_interval = current_interval;
  }

  return cents_intervals;
}

std::vector<float> Scale::ConvertDiatonicIntervalsToCents(
    const std::vector<size_t> &diatonic_intervals) {
  if (diatonic_intervals.size() < 2) {
    throw std::out_of_range(
        "Provided diatonic intervals have less than one interval");
  }

  std::vector<float> cents_intervals;

  float last_interval = 0;
  for (size_t interval_idx = 1;
       interval_idx < diatonic_intervals.size();
       ++interval_idx) {
    size_t current_interval = diatonic_intervals[interval_idx];
    if (current_interval < 0 || current_interval > 11) {
      throw std::out_of_range("Provided diatonic intervals out of range");
    }

    // 100 cents in a semitone
    float interval_cents = 100 * current_interval;
    cents_intervals.push_back(interval_cents - last_interval);
    last_interval = interval_cents;
  }

  return cents_intervals;
}

std::vector<float> Scale::ConvertFrequenciesToCents(
    const std::vector<float> &frequencies) {
  if (frequencies.size() < 2) {
    throw std::out_of_range("Provided frequencies have less than one interval");
  }

  std::vector<float> cents_intervals;

  float last_interval = 0;
  for (size_t freq_idx = 1;
       freq_idx < frequencies.size();
       ++freq_idx) {
    float cents_interval =
        kCentsInOctave * std::log2(frequencies[freq_idx] / frequencies[0]);
    cents_intervals.push_back(cents_interval - last_interval);
    last_interval = cents_interval;
  }

  return cents_intervals;
}


}

