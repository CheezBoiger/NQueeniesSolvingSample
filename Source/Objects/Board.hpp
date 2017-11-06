// Copyright (c) 2017 Mario Garcia, MIT License
#pragma once

#include "Types.hpp"

#include <vector>
#include <string>
#include <ostream>


namespace nq {


// Queen coordinates inside the board. 
typedef size_t queen_coord_t;

// Board state that Handles the current board and the queens that
// are within it. We use this board for working on solving the
// N-Queens problem.
// We represent our board as a one dimensional array, with our 
// queens coordinates stored inside.
class Board {
public:
  // Constructors.
  Board(uint32 size = 8)
    : m_board(std::vector<queen_coord_t>(size))
  {
  }

  Board(const Board &board) 
    : m_board(board.m_board)
  { }

  Board(Board &&board) { 
    std::swap(board.m_board, m_board);
  }

  Board &operator=(const Board &board) {
    m_board = board.m_board; 
    return (*this);
  }

  Board &operator=(Board &&board) {
    std::swap(m_board, board.m_board);    
    return (*this);
  }

  // Get the raw board inside this object. This will allow
  // manipulation of the board. 
  std::vector<queen_coord_t> &get_raw() {
    return m_board;
  }

  // Overload to get the coordinates of a queen safely.
  queen_coord_t &operator[](const uint32 queen) {
    return m_board[queen];
  }

  // Get the overall board size.
  size_t get_board_size() const { 
    return m_board.size();
  }

  // Moves a queen at a certain spot, provided the queen and the movement position
  // upward or downward..
  // Remember that every queen must be in separate rows. No two queens 
  // must be in the same row, column, or diagonal.
  void MoveQueenVertically(size_t queen, size_t up) {
    if (queen >= m_board.size() || up >= m_board.size()) {
      return;
    }
    m_board[queen] = up;
  }

  void Randomize();

private:
  // The actual board implementation. Technically, no board is actually
  // stored, since our concern is not about every single status information
  // about each tile, but about the ones with queen tiles already occupied.
  // So here, we implement our board as a one dimensional array consisting
  // of queens in separate columns, with numbers representing the row index
  // they sit in.
  std::vector<queen_coord_t> m_board;
};

// Overloading the output stream to see this board.
std::ostream &operator<<(std::ostream &o, Board &board);
} // nq