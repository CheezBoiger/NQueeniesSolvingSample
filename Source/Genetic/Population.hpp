// Copyright (c) 2017 Mario Garica, MIT License.
#pragma once

#include "Types.hpp"
#include "Objects/Board.hpp"

#include <vector>
#include <algorithm>
#include <functional>


namespace nq {


typedef uint32 fitness_t;
typedef std::function<fitness_t(Board &)> FitnessFunction;

// Chromosomes define a chromosome with a board state and a fitness value.
// This fitness value determines if this chromosome is worthy of mutation
// and crossover.
struct Chromosome {
  real32    selection_probability;
  fitness_t fitness;
  Board     board;
};


// We define a population set of solutions for our N-Queen problem.
class Population {

  Population() { }

public:
  // Staandard constructors.
  Population(uint32 population_size, size_t N = 8);

  Population(Population &&p) 
    : board_size(p.board_size)
    , mutation_probability(p.mutation_probability)
    , f_x(p.f_x)
  {
    std::swap(chromosomes, p.chromosomes);
  }


  Population &operator=(Population &&p) {
    board_size = p.board_size;
    mutation_probability = p.mutation_probability;
    f_x = p.f_x;
    std::swap(chromosomes, p.chromosomes);
  }
    
  // Get the fitness function being used by this Population object.
  // This is used to calculate our fitness values for our chromosomes,
  // which will then increase the chances in the selection process to 
  // be picked for cross over.
  FitnessFunction get_fitness_function() const { 
    return f_x;
  }

  // Performs Selection, Crossover, and Mutation on this population,
  // to generate and output a new population.
  Population &GenerateNewPopulationFromThis();

  // Get the best chromosome from this population.
  Chromosome &get_best();

  // Set the mutation probability manually.
  void set_mutation_probability(real32 prob) {
    mutation_probability = (prob > 0 ? prob : -prob);
  }

private:

  // Initial Generate of our Chromosomes.
  void GenerateChromosomes();
  
  // Mutate a chromosome based on the mutation probability.
  void Mutate(Chromosome &chromosome);

  // Make a CrossOver on the child between parent 0 and parent 1, along
  // the crossover point, and determining which side of each parent to 
  // splice over.
  void CrossOver(Chromosome &child, Chromosome &p0, Chromosome &p1, 
    bool splice, size_t crossover_point);

  // Make a selection based on the weighted values for each fitness.
  size_t MakeSelection();

  size_t board_size;
  real32 mutation_probability;
  FitnessFunction f_x;
  std::vector<Chromosome> chromosomes;
};
} // nq