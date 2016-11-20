#ifndef MS_RCPSP_RESOURCE_H_
#define MS_RCPSP_RESOURCE_H_

namespace SchedulingProblem {

class Resource {
 public:
  Resource(int id_, double salary_) : id_(id_), salary_(salary_) {}

  inline int id() const { return id_; }
  inline double salary() const { return salary_; }

 private:
  int id_;
  double salary_;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_RESOURCE_H_
