#include<stdint.h>
#include<iostream>
#include<cctype>
#include<map>
#include<array>

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

  //Game game;
  //std::cout << game.is_checked(true) << "\n";

  //std::array<int, 2> row_and_col = get_row_col_from_position(1);
  //std::cout << "row " << row_and_col[0] << " col " << row_and_col[1] << "\n";

  Board board(true);
  board.set_piece_position(0x100, KING, true);
  board.set_piece_position(1, QUEEN, false);
  board.print_board();

  MoveGenerator move_gen;

  //move_gen.generate_evasion_moves(&board, true);
  //move_gen.generate_evasion_moves(&board, true);

  std::vector<Move> legal_moves = move_gen.generate_legal_moves(&board, true);
  for(int i = 0; i < legal_moves.size(); i++) {
    legal_moves[i].print_move();
  }


  return 0;
}
