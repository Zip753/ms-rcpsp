#include "../include/TournamentSelector.h"

#include "../include/Random.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

template <class T>
T* TournamentSelector<T>::Select(const Population <T> &p) const {
  size_t p_size = p.size();
  size_t tourn_size = tournament_size_;
  if (p_size < tourn_size)
    tourn_size = p_size;

  int best_fitness = 0;
  size_t best_id = 0;
  for (size_t i = 0; i < tourn_size; i++) {
    size_t idx = Util::Random::randint() % p_size;
    if (i == 0 || best_fitness > p.specimen(idx)->Fitness()) {
      best_id = idx;
      best_fitness = p.specimen(idx)->Fitness();
    }
  }

  return p.specimen(best_id);
}

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
