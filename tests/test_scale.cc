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
  SECTION("2 TET") {
    const size_t num_divisions = 2;
    const float kExpectedInterval = 600;
    const std::string kExpectedName = "Chromatic Scale 2 TET";

    Scale test_scale = Scale(num_divisions);

    REQUIRE(test_scale.GetNumIntervals() == num_divisions - 1);
    REQUIRE(test_scale.GetName() == kExpectedName);
    REQUIRE(test_scale.GetInterval(0) == kExpectedInterval);
  }

  SECTION("24 TET") {
    const size_t num_divisions = 24;
    const float kExpectedInterval = 50;
    const std::string kExpectedName = "Chromatic Scale 24 TET";

    Scale test_scale = Scale(num_divisions);

    REQUIRE(test_scale.GetNumIntervals() == num_divisions - 1);
    REQUIRE(test_scale.GetName() == kExpectedName);

    for (size_t inter_idx = 0; inter_idx < num_divisions - 1; ++inter_idx) {
      REQUIRE(test_scale.GetInterval(inter_idx) == Approx(kExpectedInterval));
    }
  }

  SECTION("1200 TET") {
    const size_t num_divisions = 1200;
    const float kExpectedInterval = 1;
    const std::string kExpectedName = "Chromatic Scale 1200 TET";

    Scale test_scale = Scale(num_divisions);

    REQUIRE(test_scale.GetNumIntervals() == num_divisions - 1);
    REQUIRE(test_scale.GetName() == kExpectedName);

    for (size_t inter_idx = 0; inter_idx < num_divisions - 1; ++inter_idx) {
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
    Scale test_scale_one = Scale(2);
    Scale test_scale_two = Scale(2);

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
        test_scale.UpdateIntervalSize(2, 2.01), std::out_of_range);
  }
}

TEST_CASE("Calculate Note Frequency Valid") {
  SECTION("12 TET Chromatic Note 0") {
    const double kExpectedFreq = 440;
    Scale test_scale(12);

    double freq = test_scale.CalculateNoteFrequency(0);

    REQUIRE(freq == Approx(kExpectedFreq));
  }

  SECTION("12 TET Chromatic Note 5") {
    const double kExpectedFreq = 587.3296;
    Scale test_scale(12);

    double freq = test_scale.CalculateNoteFrequency(5);

    REQUIRE(freq == Approx(kExpectedFreq));
  }

  SECTION("12 TET Chromatic Note 11") {
    const double kExpectedFreq = 830.60956;
    Scale test_scale(12);

    double freq = test_scale.CalculateNoteFrequency(11);

    REQUIRE(freq == Approx(kExpectedFreq));
  }

  SECTION("Just Tuned Major Note 3") {
    const double kExpectedFreq = 528;
    std::vector<float> just_major_intervals = {111.73, 92.18, 111.73,
                                               70.67, 111.73, 84.47,
                                               119.45, 111.73, 70.67,
                                               111.73, 92.18};
    Scale test_scale("Just Major", just_major_intervals);

    double freq = test_scale.CalculateNoteFrequency(3);

    REQUIRE(freq == Approx(kExpectedFreq));
  }

  SECTION("12 TET Chromatic Note 11 8va") {
    const double kExpectedFreq = 2 * 830.60956;
    Scale test_scale(12);

    double freq = test_scale.CalculateNoteFrequency(23);

    REQUIRE(freq == Approx(kExpectedFreq));
  }

  SECTION("Just Tuned Major Note 3 16va") {
    const double kExpectedFreq = 4 * 528;
    std::vector<float> just_major_intervals = {111.73, 92.18, 111.73,
                                               70.67, 111.73, 84.47,
                                               119.45, 111.73, 70.67,
                                               111.73, 92.18};
    Scale test_scale("Just Major", just_major_intervals);

    double freq = test_scale.CalculateNoteFrequency(27);

    REQUIRE(freq == Approx(kExpectedFreq));
  }

  SECTION("Multi-octave second octave") {
    std::vector<float> bolivian_freqs = {440, 550, 653.125,
                                         816.4062, 969.4824, 1151.2603,
                                         1439.0754, 1708.9021};

    std::vector<float> bolivian_intervals =
        Scale::ConvertFrequenciesToCents(bolivian_freqs);

    Scale test_scale("Bolivian", bolivian_intervals, "", 2);

    double freq = test_scale.CalculateNoteFrequency(6);

    REQUIRE(freq == Approx(bolivian_freqs[6]));
  }

  SECTION("Multi-octave second octave 8va") {
    std::vector<float> bolivian_freqs = {440, 550, 653.125,
                                         816.4062, 969.4824, 1151.2603,
                                         1439.0754, 1708.9021};

    std::vector<float> bolivian_intervals =
        Scale::ConvertFrequenciesToCents(bolivian_freqs);

    Scale test_scale("Bolivian", bolivian_intervals, "", 2);

    double freq = test_scale.CalculateNoteFrequency(8);

    REQUIRE(freq == Approx(4 * bolivian_freqs[0]));
  }
}

TEST_CASE("Calculate Note Frequency Invalid") {
  SECTION("Negative frequency") {
    Scale test_scale(12);

    REQUIRE_THROWS_AS(
        test_scale.CalculateNoteFrequency(1, -440), std::out_of_range);
  }
}

TEST_CASE("Append interval to scale valid") {
  Scale test_scale("asdf", {100, 100, 100});

  test_scale.AppendInterval(100);

  REQUIRE(test_scale.GetNumIntervals() == 4);
  REQUIRE(test_scale.GetInterval(3) == 100);
}

TEST_CASE("Append interval to scale invalid") {
  SECTION("Append interval too small") {
    Scale test_scale("asdf", {100, 100, 100});

    REQUIRE_THROWS_AS(test_scale.AppendInterval(0.99), std::runtime_error);
    REQUIRE(test_scale.GetNumIntervals() == 3);
  }

  SECTION("Append interval exceeds octave") {
    Scale test_scale("asdf", {100, 100, 100});

    REQUIRE_THROWS_AS(test_scale.AppendInterval(901), std::out_of_range);
    REQUIRE(test_scale.GetNumIntervals() == 3);
  }
}

TEST_CASE("Remove interval from scale valid") {
  Scale test_scale("asdf", {100, 100});

  test_scale.RemoveInterval();

  REQUIRE(test_scale.GetNumIntervals() == 1);
  REQUIRE(test_scale.GetInterval(0) == 100);
}

TEST_CASE("Remove interval from scale invalid") {
  SECTION("Remove interval from singleton scale") {
    Scale test_scale("asdf", {100});

    REQUIRE_THROWS_AS(test_scale.RemoveInterval(), std::out_of_range);
    REQUIRE(test_scale.GetNumIntervals() == 1);
  }
}

TEST_CASE("Convert diatonic intervals to cents valid") {
  SECTION("One-note scale") {
    const std::vector<size_t> kIntervals = {0, 3};
    const std::vector<float> kExpected = {300};

    REQUIRE(Scale::ConvertDiatonicIntervalsToCents(kIntervals) == kExpected);
  }

  SECTION("Multi-note scale") {
    const std::vector<size_t> kIntervals = {0, 3, 5, 6, 7, 10};
    const std::vector<float> kExpected = {300, 200, 100, 100, 300};

    std::vector<float> out = Scale::ConvertDiatonicIntervalsToCents(kIntervals);
    REQUIRE(out == kExpected);
  }
}

TEST_CASE("Convert frequencies to cents valid") {
  SECTION("One-note scale") {
    const std::vector<float> kIntervals = {261.6255653006,
                                           315.83481057014};
    const std::vector<float> kExpected = {325.9999999999928};

    std::vector<float> outs = Scale::ConvertFrequenciesToCents(kIntervals);

    size_t idx = 0;
    for (float out : outs) {
      REQUIRE(out == Approx(kExpected[idx]));
      ++idx;
    }
  }

  SECTION("Multi-note scale") {
    const std::vector<float> kIntervals = {261.6255653006,
                                           315.83481057014,
                                           401.62159853282,
                                           478.71605466184,
                                           581.25458464818,
                                           714.36935367713,
                                           884.07587347381,
                                           1042.8816384286};
    const std::vector<float> kExpected = {325.9999999999928,
                                          416.00000000000256,
                                          304.00000000001717,
                                          335.99999999998295,
                                          356.9999999999998,
                                          369.00000000000114,
                                          286.0000000000073};

    std::vector<float> outs = Scale::ConvertFrequenciesToCents(kIntervals);

    size_t idx = 0;
    for (float out : outs) {
      REQUIRE(out == Approx(kExpected[idx]));
      ++idx;
    }
  }
}

TEST_CASE("Convert proportions to cents valid") {
  SECTION("Single octave one-note scale") {
    const std::vector<float> kProportions = {0.5};
    const std::vector<float> kExpected = {600};

    std::vector<float> outs = Scale::ConvertProportionsToCents(kProportions);

    size_t idx = 0;
    for (float out : outs) {
      REQUIRE(out == Approx(kExpected[idx]));
      ++idx;
    }
  }

  SECTION("Single octave multi-note scale") {
    const std::vector<float> kProportions = {0.25, 0.5, 0.75, 1};
    const std::vector<float> kExpected = {300, 300, 300, 300};

    std::vector<float> outs = Scale::ConvertProportionsToCents(kProportions);

    size_t idx = 0;
    for (float out : outs) {
      REQUIRE(out == Approx(kExpected[idx]));
      ++idx;
    }
  }

  SECTION("Multiple octave one-note scale") {
    const std::vector<float> kProportions = {0.5};
    const std::vector<float> kExpected = {1200};

    std::vector<float> outs = Scale::ConvertProportionsToCents(kProportions, 2);

    size_t idx = 0;
    for (float out : outs) {
      REQUIRE(out == Approx(kExpected[idx]));
      ++idx;
    }
  }

  SECTION("Multiple octave multi-note scale") {
    const std::vector<float> kProportions = {0.25, 0.5, 0.75, 1};
    const std::vector<float> kExpected = {600, 600, 600, 600};

    std::vector<float> outs = Scale::ConvertProportionsToCents(kProportions, 2);

    size_t idx = 0;
    for (float out : outs) {
      REQUIRE(out == Approx(kExpected[idx]));
      ++idx;
    }
  }
}