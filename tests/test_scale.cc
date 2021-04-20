// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <catch2/catch.hpp>
#include <core/scale.h>

using scalepiegraph::Scale;

TEST_CASE("Construct Custom Scale Invalid") {
  SECTION("No intervals") {
    REQUIRE_THROWS_AS(Scale("asdf", {}), std::out_of_range);
  }

  SECTION("More than 1200 intervals") {
    REQUIRE_THROWS_AS(
        Scale("asdf", std::vector<float>(1201, 1)), std::out_of_range);
  }

  SECTION("Intervals smaller than 1 cent") {
    REQUIRE_THROWS_AS(
        Scale("asdf", std::vector<float>(12, 0.99)), std::out_of_range);
  }

  SECTION("Span larger than 1200 cents") {
    REQUIRE_THROWS_AS(
        Scale("asdf", std::vector<float>(12, 101)), std::out_of_range);
  }
}

TEST_CASE("Construct Chromatic Scale Valid") {
  SECTION("1 TET") {
    const size_t num_divisions = 1;
    const float kExpectedInterval = 1200;
    const std::string kExpectedName = "Chromatic Scale 1 TET";

    Scale test_scale = Scale(num_divisions);

    REQUIRE(test_scale.GetNumIntervals() == num_divisions);
    REQUIRE(test_scale.GetName() == kExpectedName);
    REQUIRE(test_scale.GetInterval(0) == kExpectedInterval);
  }

  SECTION("24 TET") {
    const size_t num_divisions = 24;
    const float kExpectedInterval = 50;
    const std::string kExpectedName = "Chromatic Scale 24 TET";

    Scale test_scale = Scale(num_divisions);

    REQUIRE(test_scale.GetNumIntervals() == num_divisions);
    REQUIRE(test_scale.GetName() == kExpectedName);
    for (size_t inter_idx = 0; inter_idx < num_divisions; ++inter_idx) {
      REQUIRE(test_scale.GetInterval(inter_idx) == Approx(kExpectedInterval));
    }
  }

  SECTION("1200 TET") {
    const size_t num_divisions = 1200;
    const float kExpectedInterval = 1;
    const std::string kExpectedName = "Chromatic Scale 1200 TET";

    Scale test_scale = Scale(num_divisions);

    REQUIRE(test_scale.GetNumIntervals() == num_divisions);
    REQUIRE(test_scale.GetName() == kExpectedName);
    for (size_t inter_idx = 0; inter_idx < num_divisions; ++inter_idx) {
      REQUIRE(test_scale.GetInterval(inter_idx) == Approx(kExpectedInterval));
    }
  }
}

TEST_CASE("Construct Chromatic Scale Invalid") {
  SECTION("Zero divisions") {
    REQUIRE_THROWS_AS(Scale(0), std::out_of_range);
  }

  SECTION("More than 1200 divisions") {
    REQUIRE_THROWS_AS(Scale(1201), std::out_of_range);
  }
}



