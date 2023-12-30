/*
 * Board definitions.
 */

#pragma once

#include"Board.hpp"

// Getters:
bitboard Board::get_piece_positions(piece piece, bool white) {
  if(white) {
    return white_bitboards[piece];
  } else {
    return black_bitboards[piece];
  }
}

// Board management:
void Board::set_piece_position(bitboard position, piece piece, bool white) {
  if(white) {
    white_bitboards[piece] |= position;
  } else {
    black_bitboards[piece] |= position;
  }
}
void Board::clear_piece_position(bitboard position, piece piece, bool white) {
  if(white) {
    white_bitboards[piece] &= ~position;
  } else {
    black_bitboards[piece] &= ~position;
  }
}

// Moves:
void Board::execute_move(Move *move) {
  clear_piece_position(move->get_start_position(),
		       move->get_move_piece(),
		       move->get_white());
  set_piece_position(move->get_end_position(),
		     move->get_move_piece(),
		     move->get_white());
  if(move->get_capture_piece() != NONE) {
    clear_piece_position(move->get_start_position(),
		       move->get_capture_piece(),
		       ~move->get_white());
  }
  
}

void Board::undo_move(Move *move) {
  set_piece_position(move->get_start_position(),
		       move->get_move_piece(),
		       move->get_white());
  clear_piece_position(move->get_end_position(),
		     move->get_move_piece(),
		     move->get_white());
  if(move->get_capture_piece() != NONE) {
    set_piece_position(move->get_start_position(),
		       move->get_capture_piece(),
		       ~move->get_white());
  }
}
