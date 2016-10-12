#ifndef MS_RCPSP_VALIDATOR_H
#define MS_RCPSP_VALIDATOR_H

#include <string>

#include "Schedule.h"

namespace SchedulingProblem {

/** @brief Interface for validating schedules. */
class Validator {
 public:
  /**
   * Checks whether schedule is valid considering resource assigment, task
   * dependencies and skill requirements.
   * @param s Schedule to validate.
   * @return Pair of two elements: validity flag and output (possibly error)
   * message.
   */
  static std::pair<bool, std::string> validate(const Schedule& s);
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_VALIDATOR_H
