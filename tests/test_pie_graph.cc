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

TEST_CASE("Test get handle index") {
  SECTION("Get handle index inside bounds zero") {
    const size_t kExpectedIndex = 0;
    // Default handle radius 5
    const glm::vec2 kTestPosition(-100, 0);
    PieGraph graph(glm::vec2(0, 0), 100, {0.25, 0.5, 0.75, 1});

    graph.GetHandleIndex(kTestPosition);

    REQUIRE(graph.GetHandleIndex(kTestPosition) == kExpectedIndex);
  }

  SECTION("Get handle index inside bounds nonzero") {
    const size_t kExpectedIndex = 2;
    // Default handle radius 5
    const glm::vec2 kTestPosition(100, 0);
    PieGraph graph(glm::vec2(0, 0), 100, {0.25, 0.5, 0.75, 1});

    REQUIRE(graph.GetHandleIndex(kTestPosition) == kExpectedIndex);
  }

  SECTION("Get handle index out of bounds inside pie") {
    const size_t kExpectedIndex = -1;
    // Default handle radius 5
    const glm::vec2 kTestPosition(94, 0);
    PieGraph graph(glm::vec2(0, 0), 100, {0.25, 0.5, 0.75, 1});

    REQUIRE(graph.GetHandleIndex(kTestPosition) == kExpectedIndex);
  }

  SECTION("Get handle out of bounds outside pie") {
    const size_t kExpectedIndex = -1;
    // Default handle radius 5
    const glm::vec2 kTestPosition(106, 0);
    PieGraph graph(glm::vec2(0, 0), 100, {0.25, 0.5, 0.75, 1});

    REQUIRE(graph.GetHandleIndex(kTestPosition) == kExpectedIndex);
  }
}

