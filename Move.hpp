/*
 * Move class.
 */

#pragma once

class Move {
public:
  // Constructors:
  Move(bool a_white, bitboard a_start_position, bitboard a_end_position, piece a_move_piece, piece a_capture_piece, bool a_castle);

  // Getters:
  bool get_white(void);
  bitboard get_start_position(void);
  bitboard get_end_position(void);
  piece get_move_piece(void);
  piece get_capture_piece(void);
  bool is_castle(void);

  // Printers:
  void print_move(void);

  // Equality:
  bool move_equals(Move* other_move);

private:
  bool white;
  bitboard start_position;
  bitboard end_position;
  piece move_piece;
  piece capture_piece;
  bool castle;

  // Helpers:
  std::array<int, 2> get_row_col_from_position(bitboard position);
};
