/*
 * Move definitions.
 */

#pragma once

#include"Move.hpp"

// Constructors:
Move::Move(bool white, bitboard start_position, bitboard end_position, piece move_piece, piece capture_piece, bool castle) {
  white = white;
  start_position = start_position;
  end_position = end_position;
  move_piece = move_piece;
  capture_piece = capture_piece;
  castle = castle;
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
