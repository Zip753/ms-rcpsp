#ifndef MS_RCPSP_SCHEDULEWRITER_H_
#define MS_RCPSP_SCHEDULEWRITER_H_

#include <ostream>

#include "Schedule.h"

namespace SchedulingProblem {

/** @brief Output writer for schedule. */
class ScheduleWriter {
 public:
  /** Outputs solution to stream in compatible (.sol) format.
   * @param stream schedule output stream.*/
  static void Write(std::ostream &stream, const Schedule& s);
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SCHEDULEWRITER_H_
