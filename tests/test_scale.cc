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

TEST_CASE("Scale Equality") {
  SECTION("Scales equal single interval") {
    Scale test_scale_one = Scale(1);
    Scale test_scale_two = Scale(1);

    REQUIRE(test_scale_one == test_scale_two);
  }

  SECTION("Scales equal multiple intervals") {
    Scale test_scale_one = Scale(10);
    Scale test_scale_two = Scale(10);

    REQUIRE(test_scale_one == test_scale_two);
  }
}

TEST_CASE("Scale Inequality") {
  SECTION("Scales unequal different names") {
    Scale test_scale_one("asdf", {10, 10, 10, 10});
    Scale test_scale_two("hjkl", {10, 10, 10, 10});

    REQUIRE(test_scale_one != test_scale_two);
  }

  SECTION("Scales unequal different number intervals") {
    Scale test_scale_one("asdf", {10, 10, 10, 10});
    Scale test_scale_two("asdf", {10, 10, 10, 10, 10});

    REQUIRE(test_scale_one != test_scale_two);
  }

  SECTION("Scales unequal different interval sizes") {
    Scale test_scale_one("asdf", {10, 10, 10, 10});
    Scale test_scale_two("asdf", {10, 20, 10, 10});

    REQUIRE(test_scale_one != test_scale_two);
  }
}

TEST_CASE("Update Interval Size Valid") {
  SECTION("Reduce interval size by half") {
    Scale test_scale(12);

    test_scale.UpdateIntervalSize(0, 0.5);

    REQUIRE(test_scale.GetInterval(0) == Approx(50));
    for (size_t inter_idx = 1;
         inter_idx < test_scale.GetNumIntervals();
         ++inter_idx) {
      REQUIRE(test_scale.GetInterval(inter_idx) == Approx(100));
    }
  }

  SECTION("Increase interval size by half") {
    Scale test_scale("asdf", {100, 100, 100});

    test_scale.UpdateIntervalSize(0, 1.5);

    REQUIRE(test_scale.GetInterval(0) == Approx(150));
    for (size_t inter_idx = 1;
         inter_idx < test_scale.GetNumIntervals();
         ++inter_idx) {
      REQUIRE(test_scale.GetInterval(inter_idx) == Approx(100));
    }
  }
}

TEST_CASE("Update Interval Size Invalid") {
  SECTION("Inter index out of bounds") {
    Scale test_scale(12);

    REQUIRE_THROWS_AS(
        test_scale.UpdateIntervalSize(13, 0.5), std::out_of_range);
  }

  SECTION("Negative percent change") {
    Scale test_scale(12);

    REQUIRE_THROWS_AS(
        test_scale.UpdateIntervalSize(2, -0.5), std::runtime_error);
  }

  SECTION("Zero percent change") {
    Scale test_scale(12);

    REQUIRE_THROWS_AS(
        test_scale.UpdateIntervalSize(2, 0), std::runtime_error);
  }

  SECTION("Change exceeds octave") {
    Scale test_scale("asdf", {1});

    REQUIRE_THROWS_AS(
        test_scale.UpdateIntervalSize(0, 1201), std::out_of_range);
  }

  SECTION("Resulting scale exceeds octave") {
    Scale test_scale(12);

    REQUIRE_THROWS_AS(
        test_scale.UpdateIntervalSize(2, 1.01), std::out_of_range);
  }
}

// TEST_CASE("Calculate Note Frequency");

