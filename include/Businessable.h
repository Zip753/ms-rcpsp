#ifndef MS_RCPSP_BUSINESSABLE_H_
#define MS_RCPSP_BUSINESSABLE_H_

#include <cstddef>
#include <vector>

namespace SchedulingProblem {

/**
 * @brief Trait class used to implement LAXCrossover.
 *
 * This class is supposed to be used in Schedule implementations that want to
 * implement their own LAXCrossover specialization and have to use business
 * of resources for that. Please note that business allocation is left over to
 * the class that inherits Businessable.
 */
class Businessable {
 public:
  Businessable(size_t size) : business_(std::vector<int>(size, 0)) {}
  Businessable(const Businessable &other) : business_(other.business_) {}

  inline int business(size_t i) const { return business_[i]; }

  inline void set_business(size_t i, int new_business) {
    business_[i] = new_business;
  }

 protected:
  /** Businesses of resources. Used to implement LAXCrossover. */
  std::vector<int> business_;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_BUSINESSABLE_H_
