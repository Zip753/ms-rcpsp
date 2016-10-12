#ifndef MS_RCPSP_PROJECTREADER_H
#define MS_RCPSP_PROJECTREADER_H

#include <string>

namespace SchedulingProblem {

/** @brief Input reader of Project. */
class ProjectReader {
 public:
  /** Reads project from source file. Initializes Project singleton.
   * @return If false, input file has wrong format.
   */
  static bool read(const std::string &filename);
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PROJECTREADER_H
