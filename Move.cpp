/*
 * Move definitions.
 */

#pragma once

#include"Move.hpp"

// Constructors:
Move::Move(bool a_white, bitboard a_start_position, bitboard a_end_position, piece a_move_piece, piece a_capture_piece, bool a_castle) {
  white = a_white;
  start_position = a_start_position;
  end_position = a_end_position;
  move_piece = a_move_piece;
  capture_piece = a_capture_piece;
  castle = a_castle;
}

// Getters:
bool Move::get_white(void) {
  return white;
}

bitboard Move::get_start_position(void) {
  return start_position;
}

bitboard Move::get_end_position(void) {
  return end_position;
}

piece Move::get_move_piece(void) {
  return move_piece;
}

piece Move::get_capture_piece(void) {
  return capture_piece;
}

bool Move::is_castle(void) {
  return castle;
}

// Printers:
void Move::print_move(void) {
  std::array<int, 2> start_row_col = get_row_col_from_position(start_position);
  std::array<int, 2> end_row_col = get_row_col_from_position(end_position);

  std::cout << (char) (start_row_col[1] + 65 - 1) << start_row_col[0] << "->" << (char) (end_row_col[1] + 65 - 1) << end_row_col[0] << "\n";

  std::cout << move_piece << " -> " << capture_piece << "\n";
}

// Helpers:
std::array<int, 2> Move::get_row_col_from_position(bitboard position) {
  std::array<int, 2> row_and_col;
  bitboard mask = 1;
  int i;
  for(i = 0; i < 64; i++) {
    if(position & mask) {
      break;
    }
    mask <<= 1;
  }
  row_and_col[0] = 1 + (i / 8);
  row_and_col[1] = 8 - (i % 8);

  return row_and_col;
}

// Equality:
bool Move::move_equals(Move* other_move) {
  return white == other_move->get_white() &&
    start_position == other_move->get_start_position() &&
    end_position == other_move->get_end_position() &&
    move_piece == other_move->get_move_piece() &&
    capture_piece == other_move->get_capture_piece() &&
    castle == other_move->is_castle();
}
