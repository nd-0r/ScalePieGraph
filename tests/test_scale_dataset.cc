// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <fstream>
#include <catch2/catch.hpp>
#include <core/scale_dataset.h>

using scalepiegraph::ScaleDataset;
using scalepiegraph::Scale;

const std::string kDataDir = "/Users/andreworals/Documents/Dev/cinder_0.9.2_mac"
                             "/my-projects/scale-pie-graph/data/";

TEST_CASE("Import Dataset Valid") {
  std::ifstream file;
  const std::string kTestDataset = kDataDir + "testing/test_valid_import.json";
  const std::vector<std::string> kExpectedNames = {
      "Blues",
      "Bolivia"
  };
  const Scale kBluesScale =
      Scale("Blues",
            Scale::ConvertDiatonicIntervalsToCents({0, 3, 5, 6, 7, 10}),
            "The blues scale comprises the notes of a minor pentatonic "
            "with the flat 5, also known as the blue note. In jazz, the "
            "blues scale is used by improvising musicians.");
  const Scale kBoliviaScale =
      Scale("Bolivia",
            Scale::ConvertFrequenciesToCents({261.6255653006,
                                              315.83481057014,
                                              401.62159853282,
                                              478.71605466184,
                                              581.25458464818,
                                              714.36935367713,
                                              884.07587347381,
                                              1042.8816384286}),
            "An observed pan-pipe scale from the La Paz, Bolivia.",
            2);

  ScaleDataset dataset;
  file.open(kTestDataset);

  REQUIRE_NOTHROW(file >> dataset);
  REQUIRE(dataset.GetNames() == kExpectedNames);
  REQUIRE(dataset[kExpectedNames[0]] == kBluesScale);
  REQUIRE(dataset[kExpectedNames[1]] == kBoliviaScale);
}