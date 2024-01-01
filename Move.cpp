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
