#include "gtest/gtest.h"

#include "../../include/SimpleSchedule.h"
#include "../../include/Validator.h"

using SchedulingProblem::Project;
using SchedulingProblem::Resource;
using SchedulingProblem::SimpleSchedule;
using SchedulingProblem::Task;
using SchedulingProblem::Validator;

class SimpleScheduleTest : public ::testing::Test {
 protected:
  Project project = Project({Task(1, 3, {},  {0}),
                             Task(2, 2, {0}, {0, 1}),
                             Task(3, 5, {},  {1})},
                            {Resource(1, 5.2),
                             Resource(2, 4.7)});
  SimpleSchedule schedule = SimpleSchedule(&project);
  Validator validator;

  void SetUp() override {
    schedule.set_start(0, 1);
    schedule.set_start(1, 4);
    schedule.set_start(2, 1);
    schedule.set_capable_resource_idx(0, 0);
    schedule.set_capable_resource_idx(1, 0);
    schedule.set_capable_resource_idx(2, 0);
  }
};

TEST_F(SimpleScheduleTest, Fitness) {
  EXPECT_EQ(5, schedule.Fitness());
  EXPECT_TRUE(validator.Validate(schedule).first);
}

TEST_F(SimpleScheduleTest, TotalCost) {
  EXPECT_DOUBLE_EQ(49.5, schedule.TotalCost());
}
