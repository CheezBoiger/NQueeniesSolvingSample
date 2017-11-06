// Copyright (c) 2017 Mario Garcia, MIT License.
#include "GeneticSearch.hpp"
#include "Population.hpp"
#include "Algorithms/Algorithms.hpp"
#include "StopWatch.hpp"
#include "Common.hpp"

namespace nq {


Board GeneticSearch(const Board &init_state)
{
  Chromosome solution;
  StopWatch::Start();
  Population population(16, init_state.get_board_size());
  
  bool is_solution = false;
  float t = 0.0f;

  // Loop over until solution is reached, or time is up,
  // to which we then turn in the most fit board state.
  // If a minute passes, we need to stop the solution.
  do {
    solution = population.get_best();
    uint32 h = NumberOfAttackingQueens(solution.board);
    if (h == 0) {
      is_solution = true;
    } else {
      population.GenerateNewPopulationFromThis();
    }
    t = StopWatch::Stop();
  } while (!is_solution && (t < 60000.0f));
  
  return solution.board;
}
} // nq