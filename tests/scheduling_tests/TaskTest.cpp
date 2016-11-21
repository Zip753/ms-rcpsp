#include "gtest/gtest.h"

#include <stdexcept>

#include "../../include/Task.h"

using SchedulingProblem::Task;

class TaskTest : public ::testing::Test {
 protected:
  int id;
  int duration;
  std::vector<size_t> dependencies;
  std::vector<size_t> resource_idx;

  virtual void SetUp() override {
    id = 5;
    duration = 10;
    dependencies = {0, 2};
    resource_idx = {0, 1, 4};
  }
};

TEST_F(TaskTest, TrivialGetters) {
  Task task(id, duration, dependencies, resource_idx);
  EXPECT_EQ(5, task.id());
  EXPECT_EQ(10, task.duration());
}

TEST_F(TaskTest, Dependencies) {
  Task task(id, duration, dependencies, resource_idx);
  EXPECT_EQ(2u, task.num_dependencies());
  EXPECT_EQ(2u, task.dependency(1));
  EXPECT_THROW(task.dependency(-1), std::out_of_range);
  EXPECT_THROW(task.dependency(2), std::out_of_range);
}

TEST_F(TaskTest, CapableResources) {
  Task task(id, duration, dependencies, resource_idx);
  EXPECT_EQ(3u, task.num_capable_resources());
  EXPECT_EQ(4u, task.resource_idx(2));
  EXPECT_THROW(task.resource_idx(-1), std::out_of_range);
  EXPECT_THROW(task.resource_idx(3), std::out_of_range);
}
