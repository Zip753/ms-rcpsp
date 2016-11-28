#ifndef MS_RCPSP_PROJECTREADER_H
#define MS_RCPSP_PROJECTREADER_H

#include <memory>
#include <string>

#include "Project.h"

namespace SchedulingProblem {

/** @brief Input reader of Project. */
class ProjectReader {
 public:
  /** Reads project from source file. Initializes Project singleton.
   * @return If false, input file has wrong format.
   */
  static std::unique_ptr<Project> Read(std::istream &infile);
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PROJECTREADER_H
