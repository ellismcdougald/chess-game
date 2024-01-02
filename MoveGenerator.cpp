/*
 * MoveGenerator implementation.
 */

#pragma once

#include"MoveGenerator.hpp"

MoveGenerator::MoveGenerator() {};

extern void print_bitboard();

// Pseudo-legal move generation:
std::vector<Move> MoveGenerator::generate_king_pseudo_legal_moves(Board *board, bool white) {
  std::vector<Move> king_pseudo_legal_moves;

  bitboard king_position = board->get_piece_positions(KING, white);
  bitboard other_piece_positions = board->get_all_piece_positions(white);

  bitboard move_table = lookup_tables.get_king_move_bitboard(king_position) &
    ~other_piece_positions;

  print_bitboard(move_table);
  
  piece capture_piece;
  for(bitboard position_mask = 1; position_mask > 0; position_mask <<= 1) {
    if(move_table & position_mask) {
      capture_piece = board->get_piece_at_position(position_mask, !white);
      Move move(white, king_position, position_mask, KING, capture_piece, false);
      king_pseudo_legal_moves.push_back(move);
    }
  }

  return king_pseudo_legal_moves;
}

// Print:
void MoveGenerator::print_bitboard(bitboard bb) {
  bitboard mask = (bitboard) 1 << 63;
  for(int i = 0; i < 64; i++) {
    std::cout << (mask & bb ? 1 : 0);
    mask >>= 1;
    if((i + 1) % 8 == 0) std::cout << "\n";
  }
}
