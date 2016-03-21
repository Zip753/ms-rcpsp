#ifndef RANDOM_H
#define RANDOM_H

class Random {
public:
    static int randint();
    static bool rand(double prob);
private:
    static void seed();
    static bool _seed;
    static const int R_MAX = 1e5;
};

#endif // RANDOM_H
