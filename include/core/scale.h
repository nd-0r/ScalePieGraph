// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <vector>
#include <string>

namespace scalepiegraph {

class Scale {
 public:
  void UpdateIntervalSize(size_t interval_num, float percent_change);

  float CalculateNoteFrequency(float base_freq, size_t note_index) const;

  float GetInterval(size_t inter_num) const;

  size_t GetNumIntervals() const;

  size_t GetNumNotes() const;

  bool operator==(const Scale& other_scale) const;

  bool operator!=(const Scale& other_scale) const;

 private:
  std::string name_;
  std::vector<float> intervals_;

};

}