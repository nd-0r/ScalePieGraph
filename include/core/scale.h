// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <vector>
#include <string>
#include <cmath>

namespace scalepiegraph {

/**
 * A class representing a musical one-octave scale. Scales are stored as
 * arrays of cumulative interval sizes in cents. Furthermore, intervals
 * can be added, removed, or changed in size. Notes in the scale can be
 * converted to acoustic frequencies.
 */
class Scale {
 public:
  /**
   * Create a scale with the specified name and intervals. Scales are
   * constructed by pairwise intervals, not cumulative intervals.
   *
   * @param name The name of this Scale
   * @param intervals The intervals in this Scale
   * @param description The description of this Scale, empty by default
   * @param num_octaves The number of octaves of this Scale
   */
  Scale(const std::string& name,
        const std::vector<float>& intervals,
        const std::string& description = "",
        size_t num_octaves = 1);

  /**
   * Create a scale with the specified name and proportions. Scales are
   * constructed by cumulative intervals, not pairwise intervals.
   *
   * @param name The name of this Scale
   * @param proportions The proportions of this Scale
   * @param num_octaves The number of octaves in this Scale
   */
  Scale(const std::string& name,
        const std::vector<float>& proportions,
        size_t num_octaves);

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
   * Append an interval to this scale with the specified size.
   *
   * @param inter_size The size of the interval to add to this scale.
   */
  void AppendInterval(float inter_size);

  /**
   * Remove interval from the end of this scale.
   */
  void RemoveInterval();

  /**
   * Calculate the frequency of the specified note based on the given base
   * frequency.
   *
   * @param note_index The zero-based index of the note in this Scale whose
   * frequency to calculate.
   * @param base_freq The base frequency of this Scale; default 440
   * @return The frequency of the specified note in this Scale based on
   * he given base frequency
   */
  double CalculateNoteFrequency(size_t note_index, float base_freq=440.0) const;

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
   * Get the number of notes in this Scale. There is always
   * one more note than interval.
   *
   * @return The number of notes in this Scale
   */
   size_t GetNumNotes() const;

  /**
   * Get the cumulative intervals in this Scale as proportions between 0 and 1.
   *
   * @return The proportions in this Scale
   */
  std::vector<float> GetProportions() const;

  /**
   * Get the name of this Scale.
   *
   * @return The name of this Scale
   */
  const std::string& GetName() const;

  /**
   * Get the description of this Scale.
   *
   * @return The description of this Scale
   */
  const std::string& GetDescription() const;

  /**
   * Get the number of octaves that this Scale spans.
   *
   * @return The number of octaves that this Scale spans
   */
  size_t GetNumOctaves() const;

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

  static const float kCentsInOctave;

  /**
   * Convert proportions, in the range 0 inclusive to 1 inclusive, of a
   * specified number of octaves to log-scale cents.
   *
   * @param proportions The proportions
   * @param num_octaves The number of octaves that the proportions subdivide
   * @return The representation of these proportions as pairwise log-scale cents
   */
  static std::vector<float> ConvertProportionsToCents(
      const std::vector<float>& proportions, size_t num_octaves = 1);

  /**
   * Convert pitches, recorded as diatonic intervals, to log-scale cents.
   *
   * @param diatonic_intervals The diatonic intervals to convert to intervals
   * of cents
   * @return The cents interval representation of the diatonic intervals
   */
  static std::vector<float> ConvertDiatonicIntervalsToCents(
      const std::vector<size_t>& diatonic_intervals);

  /**
   * Convert pitches, recorded as frequencies in cycles per second (hertz), to
   * log-scale cents.
   *
   * @param frequencies The frequencies to convert to intervals of cents
   * @return The cents interval representation of the frequencies
   */
  static std::vector<float> ConvertFrequenciesToCents(
      const std::vector<float>& frequencies);
 private:
  std::string name_;
  std::string description_;
  std::vector<float> intervals_;
  size_t num_octaves_ = 1;

};

} // namespace scalepiegraph