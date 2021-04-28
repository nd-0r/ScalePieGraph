// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <catch2/catch.hpp>
#include <frontend/pie_graph.h>
#include <iostream>

using scalepiegraph::frontend::PieGraph;

TEST_CASE("Construct pie graph from proportions") {
  const std::vector<float> kExpectedProportions = {0.25, 0.75, 1};

  PieGraph graph(glm::vec2(0, 0), 1, kExpectedProportions);

  std::vector<float> out = graph.GetProportions();

  REQUIRE(kExpectedProportions.size() == out.size());
  for (size_t prop_index = 0; prop_index < out.size(); ++prop_index) {
    REQUIRE(out[prop_index] == Approx(kExpectedProportions.at(prop_index)));
  }
}

