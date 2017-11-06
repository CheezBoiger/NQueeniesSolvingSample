// Copyright (c) 2017 Mario Garcia, MIT License.
#pragma once

#include "Types.hpp"
#include "Objects/Board.hpp"

namespace nq {


// Genetic Search using populations.
Board GeneticSearch(const Board &init_state);
} // nq