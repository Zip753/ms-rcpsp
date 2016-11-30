#include "gtest/gtest.h"

#include "../../include/ProjectReader.h"

using SchedulingProblem::Project;
using SchedulingProblem::ProjectReader;
using SchedulingProblem::Resource;
using SchedulingProblem::Task;

class ProjectReaderTest : public ::testing::Test {
 protected:
  Project project = Project({
    Task(1,  37, {},     {0, 1}),
    Task(2,  36, {},     {1}),
    Task(3,  21, {},     {1, 2}),
    Task(4,  23, {},     {0, 2}),
    Task(5,  36, {},     {1, 2}),
    Task(6,  13, {},     {0, 1}),
    Task(7,  13, {3, 4}, {0, 2}),
    Task(8,  37, {},     {1, 2}),
    Task(9,  36, {6},    {0, 1}),
    Task(10, 19, {2},    {0, 2})
  }, {
    Resource(1, 56.0),
    Resource(2, 53.6),
    Resource(3, 28.9),
  });
  ProjectReader reader;
};

TEST_F(ProjectReaderTest, Read) {
  std::istringstream stream(
      "========================================================== \n"
          "File name: 10_3_5_3.def\n"
          "Creation date: Thu Oct 30 17:39:39 CET 2014\n"
          "Website: http://imopse.ii.pwr.edu.pl/ \n"
          "Reference: \n"
          "Myszkowski P. B., Skowronski M. E., Olech L., Oslizlo K., \n"
          "Hybrid Ant Colony Optimization in solving Multi-Skill Resource-Constrained Project Scheduling Problem, \n"
          "Soft Computing, DOI: DOI 10.1007/s00500-014-1455-x \n"
          "========================================================== \n"
          "General characteristics: \n"
          "Tasks: 10\n"
          "Resources: 3\n"
          "Precedence relations: 4\n"
          "Number of skill types: 3\n"
          "========================================================== \n"
          "ResourceID   Salary    Skills \n"
          "1     56.0     Q1: 0    Q2: 1    \n"
          "2     53.6     Q2: 2    Q0: 1    \n"
          "3     28.9     Q0: 1    Q1: 0    \n"
          "========================================================== \n"
          "TaskID   Duration    Skill   Predecessor IDs \n"
          "1     37   Q2: 1    \n"
          "2     36   Q2: 2    \n"
          "3     21   Q0: 1    \n"
          "4     23   Q1: 0    \n"
          "5     36   Q0: 1    \n"
          "6     13   Q2: 1    \n"
          "7     13   Q1: 0    4 5 \n"
          "8     37   Q0: 1    \n"
          "9     36   Q2: 1    7 \n"
          "10      19   Q1: 0    3 \n"
          "========================================================== \n");
  std::unique_ptr<Project> result = reader.Read(stream);
  EXPECT_EQ(project.size(), result->size());
  EXPECT_EQ(project.num_resources(), result->num_resources());

  for (size_t i = 0; i < project.num_resources(); ++i) {
    EXPECT_EQ(project.resource(i).id(), result->resource(i).id())
        << "Resource index: " << i;
    EXPECT_EQ(project.resource(i).salary(), result->resource(i).salary())
        << "Resource index: " << i;
  }

  for (size_t i = 0; i < project.size(); ++i) {
    EXPECT_EQ(project.task(i).id(), result->task(i).id())
        << "Task index: " << i;
    EXPECT_EQ(project.task(i).duration(), result->task(i).duration())
        << "Task index: " << i;

    EXPECT_EQ(project.task(i).num_dependencies(),
              result->task(i).num_dependencies()) << "Task index: " << i;
    for (size_t j = 0; j < project.task(i).num_dependencies(); ++j) {
      EXPECT_EQ(project.task(i).dependency(j), result->task(i).dependency(j))
          << "Task index: " << i << ", dependency index: " << j;
    }

    EXPECT_EQ(project.task(i).num_capable_resources(),
              result->task(i).num_capable_resources()) << "Task index: " << i;
    for (size_t j = 0; j < project.task(i).num_capable_resources(); ++j) {
      EXPECT_EQ(project.task(i).resource_idx(j),
                result->task(i).resource_idx(j))
                << "Task index: " << i << ", dependency index: " << j;
    }
  }
}
