#include "../include/Mutator.h"
#include "../include/Random.h"

Schedule* Mutator::mutate(Schedule* sample) {
    Schedule *s = new Schedule(sample);

    for (int i = 0; i < s->size(); i++) {
        // don't forget to check whether we can mutate it at all
        if (Random::rand(p_mut)) {
            mutate_gene(s, i);
        }

        if (Random::rand(p_mut)) {
            if (Random::rand(0.5)) sample->prio[i]++;
            else sample->prio[i]--;
            //int idx = Random::randint() % (s->size() - 1);
            //if (idx >= i) idx++;
            //std::swap(sample->prio[i], sample->prio[idx]);
        }
    }
    return s;
}

void Mutator::force_mutate(Schedule* sample) {
    int idx = Random::randint() % sample->size();
    mutate_gene(sample, idx);
}

void Mutator::mutate_gene(Schedule *sample, int i) {
    int max_ires = sample->max_res_count(i);
    if (max_ires > 1) {
        int new_res = Random::randint() % (max_ires - 1);
        if (new_res < sample->ires[i])
            sample->ires[i] = new_res;
        else
            sample->ires[i] = new_res + 1;
    }
}


