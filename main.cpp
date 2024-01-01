#include<stdint.h>
#include<iostream>

#include"globals.hpp"
#include"Move.cpp"
#include"Board.cpp"

bitboard generate_position(char col, char row, bool white) {
  if(white) {
    return (bitboard) 1 << (8 - col) << (row - 1) * 8;
  } else {
    return (bitboard) 1 << (8 - col) << (8 - row) * 8;
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

bitboard flip_bitboard(bitboard bb) {
  return ( (bb << 56)                           ) |
    ( (bb << 40) & bitboard(0x00ff000000000000) ) |
    ( (bb << 24) & bitboard(0x0000ff0000000000) ) |
    ( (bb <<  8) & bitboard(0x000000ff00000000) ) |
    ( (bb >>  8) & bitboard(0x00000000ff000000) ) |
    ( (bb >> 24) & bitboard(0x0000000000ff0000) ) |
    ( (bb >> 40) & bitboard(0x000000000000ff00) ) |
    ( (bb >> 56) );
}

int main(void) {
  Board board(false);
  board.print_board();

  Move move_one(true,
		generate_position(4, 2, true),
		generate_position(4, 4, true),
		PAWN,
		NONE,
		false);
  board.execute_move(&move_one);

  Move move_two(false,
		generate_position(4, 7, false),
		generate_position(4, 5, false),
		PAWN,
		NONE,
		false);
  board.execute_move(&move_two);

  board.print_board();
	       

  return 0;
}
