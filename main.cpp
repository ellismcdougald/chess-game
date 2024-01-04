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

  
  
  Game game;
  game.run_game();

  return 0;

  

  
   

  //game.test_move_generator();

  //Game game;
  //std::cout << game.is_checked(true) << "\n";

  //std::array<int, 2> row_and_col = get_row_col_from_position(1);
  //std::cout << "row " << row_and_col[0] << " col " << row_and_col[1] << "\n";

  Board board(false);
  MoveGenerator move_gen;

  std::vector<Move> white_bishop_pl_moves = move_gen.generate_piece_pseudo_legal_moves(&board, true, BISHOP);
  for(int i = 0; i < white_bishop_pl_moves.size(); i++) {
    white_bishop_pl_moves[i].print_move();
  }

  return 0;

  /*
  std::vector<Move> black_pawn_pl_moves = move_gen.generate_piece_pseudo_legal_moves(&board, false, PAWN);
  for(int i = 0; i < black_pawn_pl_moves.size(); i++) {
    black_pawn_pl_moves[i].print_move();
  }
  */
  
  
  std::vector<Move> black_legal_moves = move_gen.generate_legal_moves(&board, false);
  for(int i = 0; i < black_legal_moves.size(); i++) {
    black_legal_moves[i].print_move();
  }
  



  return 0;
}
