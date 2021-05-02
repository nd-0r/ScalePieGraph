// Copyright (c) 2021 Andrew Orals. All rights reserved.
#include <catch2/catch.hpp>
#include <frontend/keyboard.h>
#include <iostream>

using scalepiegraph::frontend::Keyboard;

TEST_CASE("Test construct keyboard from divisions") {
  REQUIRE_NOTHROW(Keyboard(glm::vec2(0, 100), 100, 100, 10));
}

TEST_CASE("Test get key index") {
  Keyboard keyboard(glm::vec2(0, 100), 100, 100, 10);

  SECTION("Test get key index front in bounds") {
    const glm::vec2 kMousePos(9, 50);
    const int kExpectedIndex = 0;

    int out = keyboard.GetKeyIndex(kMousePos) == kExpectedIndex;
    REQUIRE(out);
  }

  SECTION("Test get key index middle in bounds") {
    const glm::vec2 kMousePos(49, 50);
    const int kExpectedIndex = 4;

    REQUIRE(keyboard.GetKeyIndex(kMousePos) == kExpectedIndex);
  }

  SECTION("Test get key index back in bounds") {
    const glm::vec2 kMousePos(99, 50);
    const int kExpectedIndex = 9;

    REQUIRE(keyboard.GetKeyIndex(kMousePos) == kExpectedIndex);
  }

  SECTION("Test get key index out of bounds") {
    const glm::vec2 kMousePos(9, 101);
    const int kExpectedIndex = -1;

    REQUIRE(keyboard.GetKeyIndex(kMousePos) == kExpectedIndex);
  }
}