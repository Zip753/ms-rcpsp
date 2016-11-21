#include "gtest/gtest.h"

#include "../../include/Project.h"

using SchedulingProblem::Project;
using SchedulingProblem::Resource;
using SchedulingProblem::Task;

class ProjectTest : public ::testing::Test {
 protected:
  std::vector<Task> tasks;
  std::vector<Resource> resources;

  void SetUp() override {
    tasks = {Task(1, 13, {}, {0, 1}),
             Task(2, 9, {1}, {1, 2})};
    resources = {Resource(1, 12.34),
                 Resource(2, 42.78)};
  }
};

TEST_F(ProjectTest, Tasks) {
  Project project(tasks, resources);
  EXPECT_EQ(2u, project.size());
  EXPECT_EQ(2, project.task(1).id());
  EXPECT_THROW(project.task(-1), std::out_of_range);
  EXPECT_THROW(project.task(2), std::out_of_range);
}

TEST_F(ProjectTest, Resources) {
  Project project(tasks, resources);
  EXPECT_EQ(2u, project.num_resources());
  EXPECT_EQ(1, project.resource(0).id());
  EXPECT_THROW(project.resource(-1), std::out_of_range);
  EXPECT_THROW(project.resource(2), std::out_of_range);
}
