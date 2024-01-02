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

  // Sliding Piece Moves
  bitboard generate_sliding_piece_moves(direction slide_direction, bitboard piece_position, bitboard other_piece_positions, bitboard opponent_piece_positions);

private:
  LookupTables lookup_tables;

  // Print:
  void print_bitboard(bitboard bb);

  // Helpers:
  bitboard move_direction(direction move_direction, bitboard position);
};
