#include "gtest/gtest.h"

#include "../../include/ScheduleWriter.h"
#include "../../include/SimpleSchedule.h"

using SchedulingProblem::Project;
using SchedulingProblem::Resource;
using SchedulingProblem::ScheduleWriter;
using SchedulingProblem::SimpleSchedule;
using SchedulingProblem::Task;

class ScheduleWriterTest : public ::testing::Test {
 protected:
  Project project = Project({Task(1, 3, {},  {0}),
                             Task(2, 2, {0}, {0, 1}),
                             Task(3, 5, {},  {1})},
                            {Resource(1, 5.2),
                             Resource(2, 4.7)});
  SimpleSchedule schedule = SimpleSchedule(&project);
  ScheduleWriter writer;

  void SetUp() override {
    schedule.set_start(0, 0);
    schedule.set_start(1, 4);
    schedule.set_start(2, 0);
    schedule.set_capable_resource_idx(0, 0);
    schedule.set_capable_resource_idx(1, 0);
    schedule.set_capable_resource_idx(2, 0);
  }
};

TEST_F(ScheduleWriterTest, Write) {
    std::ostringstream stream;
    writer.Write(stream, schedule);
    EXPECT_EQ(stream.str(),
              "Hour \t Resource assignments (resource ID - task ID) \n"
              "0 1-1 2-3 \n"
              "4 1-2 \n");
}
