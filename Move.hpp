/*
 * Move class.
 */

#pragma once

class Move {
public:
  // Constructors:
  Move(bool white, bitboard start_position, bitboard end_position, piece move_piece, piece capture_piece, bool castle);

  // Getters:
  bool get_white(void);
  bitboard get_start_position(void);
  bitboard get_end_position(void);
  piece get_move_piece(void);
  piece get_capture_piece(void);
  bool is_castle(void);

private:
  bool white;
  bitboard start_position;
  bitboard end_position;
  piece move_piece;
  piece capture_piece;
  bool castle;
};
