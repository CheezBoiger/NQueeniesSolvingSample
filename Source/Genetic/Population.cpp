// Copyright (c) 2017 Mario Garcia, MIT License.
#include "Population.hpp"
#include "Algorithms/Algorithms.hpp"

#include <algorithm>
#include <random>
#include "Common.hpp"

namespace nq {


std::random_device r;
std::mt19937 mt(r());


Population::Population(uint32 population_size, size_t N)
  : mutation_probability(0.15f)
  , chromosomes(std::vector<Chromosome>(population_size))
  , board_size(N)
{
  f_x = [&] (Board &board) -> fitness_t {
    uint32 h = NumberOfAttackingQueens(board);
    size_t max = board_size * (board_size - 1) / 2;
    return static_cast<uint32>(max) - h;
  };
 
  GenerateChromosomes();
}


void Population::GenerateChromosomes()
{
  fitness_t overall = 0;
  for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
    it->board = Board(static_cast<uint32>(board_size));
    it->board.Randomize();
    it->fitness = f_x(it->board);
    overall += it->fitness;
  }
  std::sort(chromosomes.begin(), chromosomes.end(), 
    [] (const Chromosome &c0, const Chromosome &c1) -> bool {
    return c0.fitness > c1.fitness;
  });

  // Calculate the weighted values of each chromosome to determine
  // better probability of obtaining the ones with the best fitness.
  for (auto it = chromosomes.begin(); it != chromosomes.end(); ++it) {
    it->selection_probability = 
      (static_cast<real32>(it->fitness) / static_cast<real32>(overall)) * 10.0f;
  }
}


Population &Population::GenerateNewPopulationFromThis()
{ 
  std::vector<Chromosome> new_population(chromosomes.size());
  std::uniform_int_distribution<size_t> gen(0, board_size - 1);
  
  bool splice = false;
  uint32 overall = 0;
  for (size_t i = 0; i < chromosomes.size(); ++i) {
    Chromosome child;
    child.board = Board(static_cast<uint32>(board_size));

    size_t crossover_point = gen(mt);
    size_t parent0 = MakeSelection();
    size_t parent1 = MakeSelection();
    CrossOver(child, chromosomes[parent0], chromosomes[parent1], 
      splice, crossover_point);
    Mutate(child);
    child.fitness = f_x(child.board);
    overall += child.fitness;
    new_population[i] = std::move(child);
    splice = (splice ? false : true);
  }

  std::sort(new_population.begin(), new_population.end(),
    [](const Chromosome &c0, const Chromosome &c1) -> bool {
    return c0.fitness > c1.fitness;
  });

  for (auto it = new_population.begin(); it != new_population.end(); ++it) {
    it->selection_probability = 
      static_cast<real32>(it->fitness) / static_cast<real32>(overall);
  }
  
  chromosomes = std::move(new_population);
  return (*this);
}


void Population::Mutate(Chromosome &chromosome)
{
  std::uniform_real_distribution<real32> mutate;
  if (mutate(mt) < mutation_probability) {
    std::uniform_int_distribution<queen_coord_t> gen(0, 
      chromosome.board.get_board_size() - 1);
  
    // Perform some sort of mutation on a uniformly random queen in the chromosome.
    queen_coord_t col = gen(mt);
    queen_coord_t row = gen(mt);
    chromosome.board.MoveQueenVertically(col, row);
  }
}


Chromosome &Population::get_best()
{
  return chromosomes.front();
}


size_t Population::MakeSelection()
{
  // Based on randomization. We check the probability of each chromosome
  // to see which route it should take.
  std::uniform_real_distribution<real32> gen;
  real32 selection = gen(mt);
  size_t i = chromosomes.size() - 1;
  for (auto it = chromosomes.rbegin(); it != chromosomes.rend(); ++it) {
    if (selection < it->selection_probability) {
      return i;
    }
    --i;
  }
  // just return the best.
  return 0;
}


void Population::CrossOver(Chromosome &child, Chromosome &p0, Chromosome &p1,
  bool splice, size_t crossover_point)
{
  auto &board = child.board.get_raw();
  if (splice) {
    std::copy(p0.board.get_raw().begin(), 
      p0.board.get_raw().begin() + crossover_point,
      board.begin());

    std::copy(p1.board.get_raw().begin() + crossover_point,
      p1.board.get_raw().end(),
      board.begin() + crossover_point);
  } else {
    std::copy(p1.board.get_raw().begin(),
      p1.board.get_raw().begin() + crossover_point,
      board.begin());

    std::copy(p0.board.get_raw().begin() + crossover_point,
      p0.board.get_raw().end(),
      board.begin() + crossover_point);
  }
}
} // nq