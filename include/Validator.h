#ifndef MS_RCPSP_VALIDATOR_H
#define MS_RCPSP_VALIDATOR_H

#include <string>

#include "Schedule.h"

class Validator {
 public:
  static std::pair<bool, std::string> validate(const Schedule& s);
};

#endif  // MS_RCPSP_VALIDATOR_H
