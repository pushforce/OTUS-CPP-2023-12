#include <gtest/gtest.h>
#include "version.hpp"

TEST(test_version, should_be_lower_than_100)
{
    EXPECT_NE(version(), 100);
}
