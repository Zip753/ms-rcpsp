#include "gtest/gtest.h"

#include "../../include/Resource.h"

using SchedulingProblem::Resource;

TEST(ResourceTest, TrivialGetters) {
  Resource r(13, 42.78);
  EXPECT_EQ(r.id(), 13);
  EXPECT_DOUBLE_EQ(r.salary(), 42.78);
}
