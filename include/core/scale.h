// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <vector>
#include <string>
#include <cmath>

namespace scalepiegraph {

class Scale {
 public:
  Scale(const std::string& name, const std::vector<float>& intervals);

  void UpdateIntervalSize(size_t inter_index, float percent_change);

  double CalculateNoteFrequency(float base_freq, size_t note_index) const;

  float GetInterval(size_t inter_index) const;

  size_t GetNumIntervals() const;

  size_t GetNumNotes() const;

  const std::string& GetName() const;

  bool operator==(const Scale& other_scale) const;

  bool operator!=(const Scale& other_scale) const;

 private:
  const float kCentsInOctave = 1200.0;

  std::string name_;
  std::vector<float> intervals_;

};

}