// Copyright (c) 2021 Andrew Orals. All rights reserved.
#pragma once

#include <map>
#include <cmath>
#include <jsoncpp/json.h>
#include <core/scale.h>

namespace scalepiegraph {

class ScaleDataset {
 public:
  ScaleDataset() = default;

  const std::vector<std::string>& GetNames() const;

  Scale& operator[](const std::string& name);

  const Scale& operator[](const std::string& name) const;

  friend std::istream& operator>>(
      std::istream& input_stream, ScaleDataset& dataset);
 private:
  std::vector<std::string> names_;
  std::map<std::string, Scale> scales_by_name_;

};

}