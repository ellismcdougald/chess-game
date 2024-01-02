#include<stdint.h>
#include<iostream>
#include<cctype>
#include<map>

#include"globals.hpp"
#include"Move.cpp"
#include"Board.cpp"
#include"LookupTables.cpp"
#include"MoveGenerator.cpp"
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
  //Game game;
  //game.run_game();

  //game.test_move_generator();

  Board board(false);
  //board.set_piece_position(1, ROOK, true);
  //board.set_piece_position(8, KING, true);
  //board.set_piece_position(0x80, ROOK, true);
  
  MoveGenerator move_gen;

  bitboard white_threat_table = move_gen.generate_threat_table(&board, true, true);
  print_bitboard(white_threat_table);

  return 0;
}
