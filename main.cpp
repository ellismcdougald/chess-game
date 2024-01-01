#include<stdint.h>
#include<iostream>

#include"globals.hpp"
#include"Move.cpp"
#include"Board.cpp"

bitboard generate_position(char row, char col) {
  return (bitboard) 1 << (8 - col) << (row - 1) * 8;
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
  Board board(false);
  board.print_board();

  bitboard bb = 0xFF00;
  //print_bitboard(bb);
  
  return 0;
}
