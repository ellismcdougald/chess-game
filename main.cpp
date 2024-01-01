#include<stdint.h>
#include<iostream>
#include<cctype>

#include"globals.hpp"
#include"Move.cpp"
#include"Board.cpp"
#include"Game.cpp"

bitboard generate_position(char col_letter, char row_number, bool white) {
  char col_number = col_letter - 97 + 1;
  if(white) {
    return (bitboard) 1 << (8 - col_number) << (row_number - 1) * 8;
  } else {
    return (bitboard) 1 << (8 - col_number) << (8 - row_number) * 8;
  }
}

void print_bitboard(bitboard bb) {
  bitboard mask = (bitboard) 1 << 63;
  for(int i = 0; i < 64; i++) {
    std::cout << (mask & bb ? 1 : 0);
    mask >>= 1;
    if((i + 1) % 8 == 0) std::cout << "\n";
  }
}

int main(void) {
  /*
  Board board(false);
  bool white_turn = true;

  char start_row, start_col, end_row, end_col;

  std::cout << "Start position (i.e. d2): ";
  std::cin >> start_col >> start_row;
  std::cout << "End position (i.e. d4): ";
  std::cin >> end_col >> end_row;

  // get pieces at start and end position
  // detect castle
  */

  Game game;
  game.run_game();
  
  return 0;
}
