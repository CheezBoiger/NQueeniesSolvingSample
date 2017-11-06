// Copyright (c) 2017 Mario Garcia, MIT License.
#include "Algorithms.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <random>

namespace nq {


// PairHashing of the col and row.
class PairHash {
public:
  size_t operator()(const std::pair<size_t, size_t> &pair) const {
    return std::hash<size_t>{ }(pair.first) 
      + std::hash<size_t>{ }(pair.second);
  }
};


// Heuristic cost for finding the total number of 
// attacking queens.
uint32 NumberOfAttackingQueens(Board &s)
{
  uint32 h = 0;
  auto &board = s.get_raw();
  for (size_t i = 0; i < board.size(); ++i) {
    for (size_t j = i + 1; j < board.size(); ++j) {
      if (board[i] == board[j]) {
        ++h;
      }

      size_t offset = j - i;
      if ((board[i] == board[j] - offset) 
        || (board[i] == board[j] + offset)) {
        ++h;
      }
    }
  }
  return h;
}


Board MakeMoveSteepestHill(Board &init_board, 
  Heuristic heuristic_function)
{
  Board best_state = init_board;
  std::unordered_map<std::pair<size_t, size_t>, uint32, PairHash> moves;
  auto &board = init_board.get_raw();
  for (size_t col = 0; col < board.size(); ++col) {
    queen_coord_t best_move = board[col];
    for (size_t row = 0; row < board.size(); ++row) {
      if (board[col] == row) {
        continue;
      }

      Board copy_board = init_board;
      copy_board.MoveQueenVertically(col, row);
      moves[std::make_pair(col, row)] = heuristic_function(copy_board);
    }
  }

  std::vector<std::pair<size_t, size_t> > best_moves;
  uint32 h_to_beat = heuristic_function(init_board);
  for (auto &key_val : moves) {
    if (key_val.second < h_to_beat) {
      h_to_beat = key_val.second;
    }
  }

  // Adds in stochastic hill climbing...
  for (auto &key_val : moves) {
    if (key_val.second == h_to_beat) {
      best_moves.push_back(key_val.first);
    }
  }

  if (best_moves.size() > 0) {
    std::random_device dev;
    std::mt19937 mt(dev());
    std::uniform_int_distribution<size_t> dis(0, best_moves.size() - 1);

    size_t pick = dis(mt);
    size_t col = best_moves[pick].first;
    size_t row = best_moves[pick].second;
    best_state.MoveQueenVertically(col, row);
  }
  return best_state;
}


// oh muh guh...
Board SteepestHillClimbing(Board &init_board, 
  Heuristic heuristic_function)
{
  uint32 h = heuristic_function(init_board);
  Board solution = init_board;

  uint32 repeated = 0;
  uint32 steps = 0;
  while (h > 0) {
    solution = MakeMoveSteepestHill(solution, heuristic_function);
    h = heuristic_function(solution);
    ++steps;
    uint32 h_temp = heuristic_function(solution);
    if (h == h_temp) {
      ++repeated;
    } else {
      repeated = 0;
    }
    
    // We've likely found our local minima.
    if (repeated >= 11) {
      break;
    }
    h = h_temp;

  }
  return solution;
}
} // nq