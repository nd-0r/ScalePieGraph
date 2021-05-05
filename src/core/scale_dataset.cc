// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/scale_dataset.h>

namespace scalepiegraph {

const std::vector<std::string>& ScaleDataset::GetNames() const {
  return names_;
}

Scale& ScaleDataset::operator[](const std::string& name) {
  return scales_by_name_.at(name);
}

const Scale& ScaleDataset::operator[](const std::string& name) const {
  return scales_by_name_.at(name);
}

std::istream& operator>>(std::istream& input_stream, ScaleDataset& dataset) {
  Json::Value root;
  input_stream >> root;

  const Json::Value scales = root["scales"];

  for (const Json::Value& scale : scales) {
    if (scale.isMember("intervals")) {
      Scale scale_to_append = ScaleDataset::ParseScaleFromIntervals(scale);

      dataset.names_.push_back(scale_to_append.GetName());
      dataset.scales_by_name_.insert(
          std::make_pair(scale_to_append.GetName(), scale_to_append));
    } else if (scale.isMember("frequencies")) {
      Scale scale_to_append = ScaleDataset::ParseScaleFromFrequencies(scale);

      dataset.names_.push_back(scale_to_append.GetName());
      dataset.scales_by_name_.insert(
          std::make_pair(scale_to_append.GetName(), scale_to_append));
    } else {
      throw std::runtime_error("Provided scale has no notes.");
    }
  }

  return input_stream;
}

Scale ScaleDataset::ParseScaleFromIntervals(const Json::Value &context) {
  std::string name = context["name"].asString();
  std::string description;

  try {
    description = context["description"].asString();
  } catch (std::exception&) {
    description = ""; // No description available
  }

  std::vector<size_t> intervals;

  for (const Json::Value& interval : context["intervals"]) {
    intervals.push_back(interval.asUInt());
  }

  Scale scale(
      name, Scale::ConvertDiatonicIntervalsToCents(intervals), description);

  return scale;
}

Scale ScaleDataset::ParseScaleFromFrequencies(const Json::Value &context) {
  std::string name = context["name"].asString();
  std::string description;

  try {
    description = context["description"].asString();
  } catch (std::exception&) {
    description = ""; // No description available
  }

  std::vector<float> frequencies;
  size_t num_octaves;

  for (const Json::Value& frequency : context["frequencies"]) {
    frequencies.push_back(frequency.asFloat());
  }

  // Calculate number of octaves that the scale spans
  num_octaves =
      std::ceil(std::log2(frequencies.back() / frequencies.front()));

  Scale scale_to_append(name,
                        Scale::ConvertFrequenciesToCents(frequencies),
                        description,
                        num_octaves);

  return scale_to_append;
}

} // scalepiegraph