/*
 * MoveGenerator class.
 */

#pragma once

class MoveGenerator {
public:
  MoveGenerator();

  // Pseudo-legal move generation:
  std::vector<Move> generate_king_pseudo_legal_moves(Board* board, bool white);

  // Castling:
  std::vector<Move> generate_castle_moves();

  // Legal moves:
  std::vector<Move> generate_legal_moves();

private:
  LookupTables lookup_tables;

  // Print:
  void print_bitboard(bitboard bb);
};
