#ifndef MS_RCPSP_RANDOM_H
#define MS_RCPSP_RANDOM_H

class Random {
 public:
  static int randint();
  static bool rand(double prob);

 private:
  static void seed();
  static bool _seed;
};

#endif // MS_RCPSP_RANDOM_H
