// Copyright (c) 2017 Mario Garcia, MIT License.
#pragma once

#include "Types.hpp"
#include "Objects/Board.hpp"
#include <functional>

namespace nq {


// Algorithm anonymous functions. Algorithm Defines the 

// Heuristic is the function pointer used to define a heuristic
// for our search algorithm.
typedef std::function<uint32(Board &)> Heuristic;

// Algorithm is a function pointer associated with the search algorithm 
// we are using.
typedef std::function<Board(Board &, Heuristic)> Algorithm;

//
// Algorithms to use for the project.

// Steepest Hill Climbing algorithm.
// <param> init_state : the initial state to start our algorithm.
// <returns> The Modified state at the peak when our heuristic function 
//            equates to 0.
Board SteepestHillClimbing(Board &init_state, Heuristic heuristic_function);

//
// Heuristics for testing.
uint32 NumberOfAttackingQueens(Board &state);
} // nq