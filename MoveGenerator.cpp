/*
 * MoveGenerator implementation.
 */

#pragma once

#include"MoveGenerator.hpp"

MoveGenerator::MoveGenerator() {};

// Legal moves:
bool MoveGenerator::is_move_legal(Move* move, Board* board) {
  /*
   * Executes move, then checks if king is in check, then undoes move.
   */
  board->execute_move(move);
  bool is_check = is_checked(board, move->get_white());
  board->undo_move(move);

  return !is_check;
}

std::vector<Move> MoveGenerator::generate_legal_moves(Board* board, bool white) {
  std::vector<Move> legal_moves;
  std::vector<Move> piece_pseudo_legal_moves[6];
  piece_pseudo_legal_moves[KING] = generate_piece_pseudo_legal_moves(board, white, KING);
  piece_pseudo_legal_moves[QUEEN] = generate_piece_pseudo_legal_moves(board, white, QUEEN);
  piece_pseudo_legal_moves[ROOK] = generate_piece_pseudo_legal_moves(board, white, ROOK);
  piece_pseudo_legal_moves[BISHOP] = generate_piece_pseudo_legal_moves(board, white, BISHOP);
  piece_pseudo_legal_moves[KNIGHT] = generate_piece_pseudo_legal_moves(board, white, KNIGHT);
  piece_pseudo_legal_moves[PAWN] = generate_piece_pseudo_legal_moves(board, white, PAWN);

  for(int piece_index = 0; piece_index < 6; piece_index++) {
    for(int i = 0; i < piece_pseudo_legal_moves[piece_index].size(); i++) {
      if(is_move_legal(&piece_pseudo_legal_moves[piece_index][i], board)) {
	legal_moves.push_back(piece_pseudo_legal_moves[piece_index][i]);
      }
    }
  }
		
  return legal_moves;
}

// Pseudo-legal move generation:
std::vector<Move> MoveGenerator::generate_king_pseudo_legal_moves(Board *board, bool white) {
  std::vector<Move> king_pseudo_legal_moves;

  bitboard king_position = board->get_piece_positions(KING, white);
  bitboard other_piece_positions = board->get_all_piece_positions(white);

  bitboard move_table = lookup_tables.get_king_move_bitboard(king_position) &
    ~other_piece_positions;

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

std::vector<Move> MoveGenerator::generate_piece_pseudo_legal_moves(Board* board, bool white, piece move_piece) {
  std::vector<Move> piece_pseudo_legal_moves;

  bitboard piece_positions = board->get_piece_positions(move_piece, white);
  bitboard other_piece_positions = board->get_all_piece_positions(white) & ~piece_positions;
  bitboard opponent_piece_positions = board->flip_bitboard(board->get_all_piece_positions(!white));

  bitboard move_table;
  piece capture_piece;
  // outer loop finds piece positions
  for(bitboard piece_position_mask = 1; piece_position_mask > 0; piece_position_mask <<= 1) {
    if(piece_positions & piece_position_mask) {
      move_table = get_move_table_by_piece(move_piece, piece_position_mask, other_piece_positions, opponent_piece_positions);
      for(bitboard move_mask = 1; move_mask > 0; move_mask <<= 1) {
	if(move_table & move_mask) {
	  capture_piece = board->get_piece_at_position(move_mask, !white);
	  Move move(white, piece_position_mask, move_mask, move_piece, capture_piece, false);
	  piece_pseudo_legal_moves.push_back(move);
	}
      }
    }
  }

  return piece_pseudo_legal_moves;
}

// King Moves:
// IN PROGRESS
std::vector<Move> MoveGenerator::generate_evasion_moves(Board* board, bool white) {
  std::vector<Move> evasion_moves;

  bitboard king_position = board->get_piece_positions(KING, white);
  std::array<bitboard, 6> king_attackers_by_piece = get_attackers_to_position_by_piece(board, king_position, !white);
  bitboard king_attacker_locations = get_attackers_to_position(board, king_position, !white);
  int num_attackers = count_attackers(king_attackers_by_piece);
  bitboard threatened_squares = board->flip_bitboard(generate_threat_table(board, !white, true));

  // king moves
  bitboard king_moves = lookup_tables.get_king_move_bitboard(king_position) & ~threatened_squares;
  print_bitboard(king_moves);

  bitboard other_piece_positions = board->get_all_piece_positions(white);
  bitboard opponent_piece_positions = board->get_all_piece_positions(!white);

  // if more than one, only king moves
  // else we consider captures or blocks

  // capture moves
  bitboard piece_positions, piece_move_bitboard, current_position, attack_ray;
  piece piece_type, attacker_piece_type;
  for(int piece_index = 0; piece_index < 6; piece_index++) {
    piece_type = board->get_piece_from_index(piece_index);
    piece_positions = board->get_piece_positions(piece_type, white);


    for(bitboard position_mask = 1; position_mask > 0; position_mask <<= 1) {
      current_position = piece_positions & position_mask;
      if(current_position) {
	piece_move_bitboard = get_move_table_by_piece(piece_type, current_position, other_piece_positions & ~current_position, opponent_piece_positions);
	for(int attacker_piece_index = 0; attacker_piece_index < 6; attacker_piece_index++ ) {
	  attacker_piece_type = board->get_piece_from_index(attacker_piece_index);
	  if(piece_move_bitboard & king_attackers_by_piece[attacker_piece_index]) {
	    Move move(white, current_position, piece_move_bitboard & king_attackers_by_piece[attacker_piece_index], piece_type, attacker_piece_type, false);
	    evasion_moves.push_back(move);
	  }
	}
      }
    }
  }

  std::cout << evasion_moves.size() << "\n";

  // Two attackers
  // capture or move to safe square
  // One attacker
  // capture, move to safe square, block sliding attack

  

  return evasion_moves;
}

// Sliding Piece Moves:
bitboard MoveGenerator::generate_sliding_piece_move_table(direction slide_direction, bitboard piece_position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  //other_piece_positions = move_direction(slide_direction, other_piece_positions);
  opponent_piece_positions = move_direction(slide_direction, opponent_piece_positions);

  bitboard result = 0;
  bitboard current_position = piece_position;
  while(current_position) {
    current_position = move_direction(slide_direction, current_position) & ~other_piece_positions & ~opponent_piece_positions;
    result |= current_position;
  } 
  
  return result;
}

// Move Tables:
bitboard MoveGenerator::generate_king_move_table(bitboard king_position, bitboard other_piece_positions) {
  return lookup_tables.get_king_move_bitboard(king_position) & ~other_piece_positions;
}
bitboard MoveGenerator::generate_pawn_move_table(bitboard pawn_position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  return (lookup_tables.get_pawn_single_push_bitboard(pawn_position) & ~other_piece_positions) |
    (lookup_tables.get_pawn_double_push_bitboard(pawn_position) & ~other_piece_positions &~opponent_piece_positions) |
    (lookup_tables.get_pawn_attack_bitboard(pawn_position) & opponent_piece_positions);
}
bitboard MoveGenerator::generate_knight_move_table(bitboard knight_position, bitboard other_piece_positions) {
  return lookup_tables.get_knight_move_bitboard(knight_position) & ~other_piece_positions;
}

bitboard MoveGenerator::generate_queen_move_table(bitboard queen_position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  return generate_sliding_piece_move_table(NORTH, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(SOUTH, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(EAST, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(WEST, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(NORTHWEST, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(NORTHEAST, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(SOUTHWEST, queen_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(SOUTHEAST, queen_position, other_piece_positions, opponent_piece_positions);
}

bitboard MoveGenerator::generate_rook_move_table(bitboard rook_position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  return generate_sliding_piece_move_table(NORTH, rook_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(SOUTH, rook_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(EAST, rook_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(WEST, rook_position, other_piece_positions, opponent_piece_positions);
}

bitboard MoveGenerator::generate_bishop_move_table(bitboard bishop_position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  return generate_sliding_piece_move_table(NORTHWEST, bishop_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(NORTHEAST, bishop_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(SOUTHWEST, bishop_position, other_piece_positions, opponent_piece_positions) |
    generate_sliding_piece_move_table(SOUTHEAST, bishop_position, other_piece_positions, opponent_piece_positions);
}

bitboard MoveGenerator::get_move_table_by_piece(piece move_piece, bitboard position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  switch(move_piece) {
  case PAWN: return generate_pawn_move_table(position, other_piece_positions, opponent_piece_positions);
  case KNIGHT: return generate_knight_move_table(position, other_piece_positions);
  case BISHOP: return generate_bishop_move_table(position, other_piece_positions, opponent_piece_positions);
  case ROOK: return generate_rook_move_table(position, other_piece_positions, opponent_piece_positions);
  case QUEEN: return generate_queen_move_table(position, other_piece_positions, opponent_piece_positions);
  case KING: return generate_king_move_table(position, other_piece_positions);
  case NONE: return 0;
  }
}

// Threat Tables:
bitboard MoveGenerator::generate_threat_table(Board *board, bool white, bool exclude_king) {
  bitboard result = 0;
  piece current_piece;
  for(bitboard position = 1; position > 0; position <<= 1) {
    current_piece = board->get_piece_at_position(position, white);
    result |= get_threats_by_piece(current_piece, board, position, white, exclude_king);
  }

  return result;
}

bitboard MoveGenerator::get_threats_by_piece(piece piece, Board *board, bitboard position, bool white, bool exclude_king) {
  bitboard other_piece_positions = board->get_all_piece_positions(white) & ~position;
  bitboard opponent_piece_positions = board->flip_bitboard(board->get_all_piece_positions(!white));
  if(exclude_king) {
    opponent_piece_positions &= ~board->flip_bitboard(board->get_piece_positions(KING, !white));
  }
  
  switch(piece) {
  case KING: return lookup_tables.get_king_move_bitboard(position);
  case QUEEN: return generate_queen_move_table(position, other_piece_positions, opponent_piece_positions);
  case ROOK: return generate_rook_move_table(position, other_piece_positions, opponent_piece_positions);
  case BISHOP: return generate_bishop_move_table(position, other_piece_positions, opponent_piece_positions);;
  case KNIGHT: return lookup_tables.get_knight_move_bitboard(position);
  case PAWN: return lookup_tables.get_pawn_attack_bitboard(position);
  case NONE: return 0;
  }
}

bitboard MoveGenerator::get_attackers_to_position(Board *board, bitboard position, bool white) {
  bitboard king_attackers = lookup_tables.get_king_move_bitboard(position) & board->get_piece_positions(KING, white);
  bitboard pawn_attackers = (SOUTHWEST(position) | SOUTHEAST(position)) & board->get_piece_positions(PAWN, white);
  bitboard knight_attackers = lookup_tables.get_knight_move_bitboard(position) & board->get_piece_positions(KNIGHT, white);

  bitboard other_piece_positions = board->get_all_piece_positions(!white) & ~position;
  bitboard opponent_piece_positions = board->flip_bitboard(board->get_all_piece_positions(white));
  
  bitboard bishop_attackers = generate_bishop_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(BISHOP, white));
  bitboard rook_attackers = generate_rook_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(ROOK, white));
  bitboard queen_attackers = generate_queen_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(QUEEN, white));

  return pawn_attackers | knight_attackers | king_attackers | bishop_attackers | rook_attackers | queen_attackers;
}

std::array<bitboard, 6> MoveGenerator::get_attackers_to_position_by_piece(Board *board, bitboard position, bool white) {
  std::array<bitboard, 6> attackers_by_piece;
  attackers_by_piece[KING] = lookup_tables.get_king_move_bitboard(position) & board->get_piece_positions(KING, white);
  attackers_by_piece[PAWN] = (SOUTHWEST(position) | SOUTHEAST(position)) & board->get_piece_positions(PAWN, white);
  attackers_by_piece[KNIGHT] = lookup_tables.get_knight_move_bitboard(position) & board->get_piece_positions(KNIGHT, white);

  bitboard other_piece_positions = board->get_all_piece_positions(white) & ~position;
  bitboard opponent_piece_positions = board->flip_bitboard(board->get_all_piece_positions(!white));
  
  attackers_by_piece[BISHOP] = generate_bishop_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(BISHOP, white));
  attackers_by_piece[ROOK] = generate_rook_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(ROOK, white));
  attackers_by_piece[QUEEN] = generate_queen_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(QUEEN, white));

  return attackers_by_piece;
}

// Check:
bool MoveGenerator::is_checked(Board* board, bool white) {
  bitboard king_position = board->get_piece_positions(KING, white);
  bitboard king_attackers = get_attackers_to_position(board, king_position, !white);
  return king_attackers;
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

// Helpers:
bitboard MoveGenerator::move_direction(direction move_direction, bitboard position) {
  switch(move_direction) {
  case NORTH: return NORTH(position);
  case SOUTH: return SOUTH(position);
  case EAST: return EAST(position);
  case WEST: return WEST(position);
  case NORTHWEST: return NORTHWEST(position);
  case NORTHEAST: return NORTHEAST(position);
  case SOUTHWEST: return SOUTHWEST(position);
  case SOUTHEAST: return SOUTHEAST(position);
  }
}

int MoveGenerator::count_attackers(std::array<bitboard, 6> attackers_by_position) {
  int attacker_count = 0;
  for(int position_index = 0; position_index < 6; position_index++) {
    attacker_count += count_bits(attackers_by_position[position_index]);
  }
  return attacker_count;
}

int MoveGenerator::count_bits(bitboard bb) {
  int bit_count = 0;
  for(bitboard position = 1; position > 0; position <<= 1) {
    if(bb & position) {
      bit_count++;
    }
  }
  return bit_count;
}
