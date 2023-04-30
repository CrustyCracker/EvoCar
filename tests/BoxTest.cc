#include <gtest/gtest.h>
/*
Author: Mateusz Krakowski
Description: This is a test file for Box class.
*/

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
