#include "gtest/gtest.h"

#include "../../include/PrioSchedule.h"

using SchedulingProblem::PrioSchedule;
using SchedulingProblem::Project;
using SchedulingProblem::Resource;
using SchedulingProblem::Task;

class PrioScheduleTest : public ::testing::Test {
 protected:
  Project project = Project({Task(1, 3, {},  {0}),
                             Task(2, 2, {0}, {0, 1}),
                             Task(3, 5, {},  {1})},
                            {Resource(1, 5.2),
                             Resource(2, 4.7)});
  PrioSchedule schedule = PrioSchedule(&project);

  void SetUp() override {
    schedule.set_start(0, 0);
    schedule.set_start(1, 4);
    schedule.set_start(2, 0);
    schedule.set_capable_resource_idx(0, 0);
    schedule.set_capable_resource_idx(1, 0);
    schedule.set_capable_resource_idx(2, 0);
  }
};

TEST_F(PrioScheduleTest, Fitness) {
  EXPECT_EQ(6, schedule.Fitness());
}

TEST_F(PrioScheduleTest, TotalCost) {
  EXPECT_DOUBLE_EQ(49.5, schedule.TotalCost());
}
