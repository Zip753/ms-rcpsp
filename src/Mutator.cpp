#include "../include/Mutator.h"
#include "../include/Random.h"

Schedule* Mutator::mutate(Schedule* sample) {
    Schedule *s = new Schedule(sample);

    for (int i = 0; i < s->size(); i++) {
        // don't forget to check whether we can mutate it at all
        int max_ires = s->max_res_count(i);
        if (max_ires > 1 && Random::rand(p_mut)) {
            int new_res = Random::randint() % (max_ires - 1);
            if (new_res < s->ires[i])
                s->ires[i] = new_res;
            else
                s->ires[i] = new_res + 1;
        }
    }
    return s;
}

Schedule* Mutator::force_mutate(Schedule* sample) {
}
