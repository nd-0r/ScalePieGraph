// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <map>
#include <cmath>
#include <jsoncpp/json.h>
#include <core/scale.h>

namespace scalepiegraph {

/**
 * A class representing a dataset of musical Scales.
 */
class ScaleDataset {
 public:
  /**
   * Default constructor for a Scale Dataset.
   */
  ScaleDataset() = default;

  /**
   * Get the names of the scales in this dataset.
   *
   * @return The names of the scales in this dataset
   */
  const std::vector<std::string>& GetNames() const;

  /**
   * Get the Scale corresponding to a specific name in this dataset.
   *
   * @param name The name of the Scale to return
   * @return The Scale with the specified name
   */
  Scale& operator[](const std::string& name);

  /**
   * Get the Scale corresponding to a specific name in this dataset.
   *
   * @param name The name of the Scale to return
   * @return The Scale with the specified name
   */
  const Scale& operator[](const std::string& name) const;

  /**
   * Load a JSON dataset of scales into this dataset
   *
   * @param input_stream The stream from which to read the JSON
   * @param dataset The dataset in which to load the parsed Scales
   * @return The consumed input stream
   */
  friend std::istream& operator>>(
      std::istream& input_stream, ScaleDataset& dataset);
 private:
  /**
   * Parse a scale's intervals represented in json to a Scale.
   *
   * @param context The json parsing context
   * @return The parsed scale
   */
  static Scale ParseScaleFromIntervals(const Json::Value& context);

  /**
   * Parse a scale's frequencies represented in json to a Scale.
   *
   * @param context The json parsing context
   * @return The parsed scale
   */
  static Scale ParseScaleFromFrequencies(const Json::Value& context);

  std::vector<std::string> names_;
  std::map<std::string, Scale> scales_by_name_;
};

} // namespace scalepiegraph