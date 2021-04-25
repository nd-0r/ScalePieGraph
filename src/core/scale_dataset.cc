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
    std::string name = scale["name"].asString();
    std::string description;

    try {
      description = scale["description"].asString();
    } catch (std::exception&) {
      description = ""; // No description available
    }

    if (scale.isMember("intervals")) {
      std::vector<size_t> intervals;

      for (const Json::Value& interval : scale["intervals"]) {
        intervals.push_back(interval.asUInt());
      }

      Scale scale_to_append(
          name, Scale::ConvertDiatonicIntervalsToCents(intervals), description);
      dataset.names_.push_back(name);
      dataset.scales_by_name_.insert(std::make_pair(name, scale_to_append));
    } else if (scale.isMember("frequencies")) {
      std::vector<float> frequencies;
      size_t num_octaves;

      for (const Json::Value& frequency : scale["frequencies"]) {
        frequencies.push_back(frequency.asFloat());
      }

      num_octaves = std::ceil(frequencies.back() / frequencies.front());

      Scale scale_to_append(name,
                            Scale::ConvertFrequenciesToCents(frequencies),
                            description,
                            num_octaves);
      dataset.names_.push_back(name);
      dataset.scales_by_name_.insert(std::make_pair(name, scale_to_append));
    } else {
      throw std::runtime_error("Provided scale has no notes.");
    }

  }

  return input_stream;
}

}