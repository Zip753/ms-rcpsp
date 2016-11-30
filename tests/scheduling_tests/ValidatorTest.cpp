#include "gtest/gtest.h"

#include "../../include/SimpleSchedule.h"
#include "../../include/Validator.h"

using SchedulingProblem::Project;
using SchedulingProblem::Resource;
using SchedulingProblem::SimpleSchedule;
using SchedulingProblem::Task;
using SchedulingProblem::Validator;

class ValidatorTest : public ::testing::Test {
 protected:
  Project project = Project({Task(1, 3, {},  {0}),
                             Task(2, 2, {0}, {0, 1}),
                             Task(3, 5, {},  {1})},
                            {Resource(1, 5.2),
                             Resource(2, 4.7)});
  SimpleSchedule schedule = SimpleSchedule(&project);
  Validator validator;
};

TEST_F(ValidatorTest, DependencyConflict) {
  schedule.set_start(0, 0);
  schedule.set_start(1, 2);
  schedule.set_start(2, 10);
  schedule.set_capable_resource_idx(0, 0);
  schedule.set_capable_resource_idx(1, 0);
  schedule.set_capable_resource_idx(2, 0);

  std::pair<bool, std::string> result = validator.Validate(schedule);
  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second,
            "Task dependency not met "
                "(task #2 start time: 2, task #1 finish time: 3).");
}

TEST_F(ValidatorTest, NegativeStartTime) {
  schedule.set_start(0, -1);
  schedule.set_start(1, 4);
  schedule.set_start(2, 3);
  schedule.set_capable_resource_idx(0, 0);
  schedule.set_capable_resource_idx(1, 0);
  schedule.set_capable_resource_idx(2, 0);

  std::pair<bool, std::string> result = validator.Validate(schedule);
  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second,
            "Negative start time (task ID: 1, start time: -1).");
}

TEST_F(ValidatorTest, ResourceConflict) {
  schedule.set_start(0, 0);
  schedule.set_start(1, 4);
  schedule.set_start(2, 0);
  schedule.set_capable_resource_idx(0, 0);
  schedule.set_capable_resource_idx(1, 1);
  schedule.set_capable_resource_idx(2, 0);

  std::pair<bool, std::string> result = validator.Validate(schedule);
  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second,
            "Resource #2 has conflicting assignments "
                "(task #3 finish time: 5, task #2 start time: 4).");
}

TEST_F(ValidatorTest, IncapableResource) {
  schedule.set_start(0, 0);
  schedule.set_start(1, 4);
  schedule.set_start(2, 0);
  schedule.set_capable_resource_idx(0, 0);
  schedule.set_capable_resource_idx(1, 1);
  schedule.set_capable_resource_idx(2, 1);

  std::pair<bool, std::string> result = validator.Validate(schedule);
  EXPECT_FALSE(result.first);
  EXPECT_EQ(result.second,
            "Resource index out of boundaries "
                "(task ID: 3, resource index: 1, capable resources: 1).");
}

TEST_F(ValidatorTest, ValidSchedule) {
  schedule.set_start(0, 0);
  schedule.set_start(1, 4);
  schedule.set_start(2, 0);
  schedule.set_capable_resource_idx(0, 0);
  schedule.set_capable_resource_idx(1, 0);
  schedule.set_capable_resource_idx(2, 0);

  std::pair<bool, std::string> result = validator.Validate(schedule);
  EXPECT_TRUE(result.first);
  EXPECT_EQ("OK", result.second);
}
