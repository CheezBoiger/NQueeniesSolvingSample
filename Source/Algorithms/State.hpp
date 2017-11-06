// Copyright (c) 2017 Mario Garcia, MIT License.
#pragma once

#include "Types.hpp"
#include "Objects/Board.hpp"

namespace nq {


class State {
public:
  State()
    { }

  State(Board &init)
    : curr_board(init)
  { }


  void StoreBoard(Board &board) { 
    curr_board = std::move(board);
  }
  
  const Board &get_board() const { 
    return curr_board;
  }

private:

  // The current board state.
  Board curr_board;
};
} // nq