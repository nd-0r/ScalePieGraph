// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <core/scale.h>

namespace scalepiegraph {

Scale::Scale(const std::string &name, const std::vector<float> &intervals) :
    name_(name), intervals_(intervals) {}

float Scale::GetInterval(size_t inter_index) const {
  if (inter_index > intervals_.size()) {
    throw std::out_of_range("Invalid interval index for this scale!");
  }

  return intervals_[inter_index];
}

size_t Scale::GetNumIntervals() const {
  return intervals_.size();
}

size_t Scale::GetNumNotes() const {
  return intervals_.size() + 1;
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

