/*
 * Board definitions.
 */

#pragma once

#include"Board.hpp"
#include"startingpositions.hpp"

// Constructors:
Board::Board(bool empty) : white_bitboards(), black_bitboards() {
  if(!empty) {
    initialize_starting_position();
  }
}

// Getters:
bitboard Board::get_piece_positions(piece piece, bool white) {
  if(white) {
    return white_bitboards[piece];
  } else {
    return black_bitboards[piece];
  }
}

// Printers:
void Board::print_board(void) {
  bitboard white_mask = (bitboard) 1 << 63;
  bitboard black_mask = 1;
  piece white_piece, black_piece;
  
  for(int i = 0; i < 64; i++) {
    white_piece = get_piece_at_position(white_mask, true);
    black_piece = get_piece_at_position(black_mask, false);

    if(white_piece != NONE) {
      std::cout << " " << get_char_from_piece(white_piece) << " ";
    } else if(black_piece != NONE) {
      std::cout << " " << get_char_from_piece(black_piece) << " ";
    } else {
      std::cout << "   ";
    }

    white_mask >>= 1;
    black_mask <<= 1;

    if((i + 1) % 8 == 0) {
      std::cout << "\n";
    } else {
      std::cout << "|";
    }
  }
}

void Board::print_piece_positions(piece p, bool white) {
  if(white) {
    print_bitboard(white_bitboards[p]);
  } else {
    print_bitboard(black_bitboards[p]);
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

// Initializers
void Board::initialize_starting_position(void) {
  std::cout << "run\n";
  set_piece_position(KING_START_POSITION, KING, true);
  set_piece_position(QUEEN_START_POSITION, QUEEN, true);
  set_piece_position(BISHOP_START_POSITION, BISHOP, true);
  set_piece_position(KNIGHT_START_POSITION, KNIGHT, true);
  set_piece_position(ROOK_START_POSITION, ROOK, true);
  set_piece_position(PAWN_START_POSITION, PAWN, true);

  set_piece_position(KING_START_POSITION, KING, false);
  set_piece_position(QUEEN_START_POSITION, QUEEN, false);
  set_piece_position(BISHOP_START_POSITION, BISHOP, false);
  set_piece_position(KNIGHT_START_POSITION, KNIGHT, false);
  set_piece_position(ROOK_START_POSITION, ROOK, false);
  set_piece_position(PAWN_START_POSITION, PAWN, false);
}

// Print
void Board::print_bitboard(bitboard bb) {
  bitboard mask = (bitboard) 1 << 63;
  for(int i = 0; i < 64; i++) {
    std::cout << (mask & bb ? 1 : 0);
    mask >>= 1;
    if((i + 1) % 8 == 0) std::cout << "\n";
  }
}

// Helpers:
piece Board::get_piece_at_position(bitboard position, bool white) {
  bitboard *bb_ptr = white ? white_bitboards : black_bitboards;
  for(int i = 0; i < 6; i++) {
    if(bb_ptr[i] & position) {
      return get_piece_from_index(i);
    }
  }
  return NONE;
}

piece Board::get_piece_from_index(int piece_index) {
  switch(piece_index) {
  case 0: return PAWN;
  case 1: return KNIGHT;
  case 2: return BISHOP;
  case 3: return ROOK;
  case 4: return QUEEN;
  case 5: return KING;
  default: return NONE;
  };
}

char Board::get_char_from_piece(piece p) {
  switch(p) {
  case PAWN: return 'P';
  case KNIGHT: return 'N';
  case BISHOP: return 'B';
  case ROOK: return 'R';
  case QUEEN: return 'Q';
  case KING: return 'K';
  default: return ' ';
  };
}
