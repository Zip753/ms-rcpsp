#include "../include/Mutator.h"
#include "../include/Random.h"

Schedule* Mutator::mutate(Schedule* sample) {
    Schedule *s = new Schedule(sample);

    for (int i = 0; i < s->size(); i++) {
        // don't forget to check whether we can mutate it at all
        if (s->ires[i] > 1 && Random::rand(p_mut)) {
            int new_res = Random::randint() % (s->max_res_count(i) - 1);
            if (new_res < s->ires[i])
                s->ires[i] = new_res;
            else
                s->ires[i] = new_res + 1;
        }
    }
    return s;
}
