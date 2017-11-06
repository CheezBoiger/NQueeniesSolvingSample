// Copyright (c) 2017 Mario Garcia, MIT License.
#include "Common.hpp"
#include "Algorithms/Algorithms.hpp"
#include "Genetic/GeneticSearch.hpp"
#include "StopWatch.hpp"
#include "Objects/Board.hpp"

#include <iomanip>


int main(int c, char *arv[])
{
  // Randomize the N-Queens board.
  nq::Board board(21);
  board.Randomize();

  // For Steepest Hill Climbing Local Minima.
  nq::StopWatch::Start();
  nq::Board b = nq::GeneticSearch(board);
  float tG = nq::StopWatch::Stop();

  nq::Board steepBoard;
  float overall = 0.0f;
  for (size_t i = 0; i < 100; ++i) {
    steepBoard.Randomize();
    // For Genetic Algorithm solving.
    nq::StopWatch::Start();
    steepBoard = nq::SteepestHillClimbing(board, nq::NumberOfAttackingQueens);
    float time = nq::StopWatch::Stop();
    if (nq::NumberOfAttackingQueens(steepBoard) == 0) {
      overall += 1.0f;
    }
  }
  float tS = overall;

  std::cout << "Initial board: " <<  board;
  std::cout << "Steepest Hill Local Minima: " << steepBoard;
  std::cout << "Genetic solved board: " << b << "\n";
  std::cout << nq::NumberOfAttackingQueens(steepBoard) << "\n";
  std::cout << "Genetic time in " << tG << " ms\n";
  std::cout << "Steepest Hill success rate: " << tS << "%\n";
  std::cout << "\nPress Enter to exit...\n";
  std::cin.ignore();
  return 0;
}