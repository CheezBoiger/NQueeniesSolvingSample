// Copyright (c) 2017 Mario Garcia, MIT License.
#include "Objects/Board.hpp"
#include <random>

namespace nq {


std::ostream &operator<<(std::ostream &o, Board &board) {
  for (auto coord : board.get_raw()) {
    o << coord << " ";
  }
  o << "\n";
  return o;
}


void Board::Randomize()
{
  std::random_device r;
  std::mt19937 twister(r());
  std::uniform_int_distribution<queen_coord_t> generator(0, m_board.size() - 1);

  for (size_t i = 0; i < m_board.size(); ++i) {
    m_board[i] = generator(twister);
  }
}
} // nq