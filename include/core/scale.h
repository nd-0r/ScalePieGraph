// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <vector>
#include <string>
#include <cmath>

namespace scalepiegraph {

/**
 * A class representing a musical one-octave scale. Scales are stored as
 * arrays of pairwise interval sizes in cents. Furthermore, intervals
 * can be added, removed, or changed in size. Notes in the scale can be
 * converted to acoustic frequencies.
 */
class Scale {
 public:
  /**
   * Create a scale with the specified name and intervals.
   *
   * @param name The name of this Scale
   * @param intervals The intervals in this Scale
   */
  Scale(const std::string& name, const std::vector<float>& intervals);

  /**
   * Create a scale with a specified number of equal-sized intervals.
   *
   * @param num_divisions The number of divisions of the octave
   */
  Scale(size_t num_divisions);

  /**
   * Update the size of an interval in this scale by a specified percentage of
   * its original size.
   *
   * @param inter_index The zero-based index of the interval to update
   * @param percent_change The proportion to change the specified interval
   */
  void UpdateIntervalSize(size_t inter_index, float percent_change);

  /**
   * Calculate the frequency of the specified note based on the given base
   * frequency.
   *
   * @param base_freq The base frequency of this Scale
   * @param note_index The zero-based index of the note in this Scale whose
   * frequency to calculate.
   * @return The frequency of the specified note in this Scale based on
   * he given base frequency
   */
  double CalculateNoteFrequency(float base_freq, size_t note_index) const;

  /**
   * Get the specified pairwise interval of this scale.
   *
   * @param inter_index The zero-based index of the interval to get
   * @return The specified interval
   */
  float GetInterval(size_t inter_index) const;

  /**
   * Get the quantity of intervals in this Scale.
   *
   * @return The quantity of intervals in this scale
   */
  size_t GetNumIntervals() const;

  /**
   * Get the name of this Scale.
   *
   * @return The name of this Scale
   */
  const std::string& GetName() const;

  /**
   * Determine if this Scale is equal to another scale. Two Scales are equal
   * if they have the same name and intervals.
   *
   * @param other_scale The other Scale with which to compare this Scale
   * @return True if the two scales are equal; otherwise, false
   */
  bool operator==(const Scale& other_scale) const;

  /**
   * Determine if this Scale is not equal to another scale. Two Scales are
   * not equal if they have different same names or intervals.
   *
   * @param other_scale The other Scale with which to compare this Scale
   * @return False if the two scales are equal; otherwise, true
   */
  bool operator!=(const Scale& other_scale) const;

 private:
  const float kCentsInOctave = 1200.0;
  std::string name_;
  std::vector<float> intervals_;

};

}