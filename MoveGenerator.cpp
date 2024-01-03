/*
 * MoveGenerator implementation.
 */

#pragma once

#include"MoveGenerator.hpp"

MoveGenerator::MoveGenerator() {};

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

// Sliding Piece Moves:
bitboard MoveGenerator::generate_sliding_piece_move_table(direction slide_direction, bitboard piece_position, bitboard other_piece_positions, bitboard opponent_piece_positions) {
  other_piece_positions = move_direction(slide_direction, other_piece_positions);
  opponent_piece_positions = move_direction(slide_direction, opponent_piece_positions);

  bitboard result = 0;
  bitboard current_position = piece_position;
  while(current_position) {
    current_position = move_direction(slide_direction, current_position) & ~other_piece_positions & ~opponent_piece_positions;
    result |= current_position;
  } 
  
  return result;
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
  bitboard attackers;
  bitboard king_attackers = lookup_tables.get_king_move_bitboard(position) & board->get_piece_positions(KING, white);
  bitboard pawn_attackers = (SOUTHWEST(position) | SOUTHEAST(position)) & board->get_piece_positions(PAWN, white);
  bitboard knight_attackers = lookup_tables.get_knight_move_bitboard(position) & board->get_piece_positions(KNIGHT, white);

  bitboard other_piece_positions = board->get_all_piece_positions(white) & ~position;
  bitboard opponent_piece_positions = board->flip_bitboard(board->get_all_piece_positions(!white));
  
  bitboard bishop_attackers = generate_bishop_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(BISHOP, white));
  bitboard rook_attackers = generate_rook_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(ROOK, white));
  bitboard queen_attackers = generate_queen_move_table(position, other_piece_positions, opponent_piece_positions) & board->flip_bitboard(board->get_piece_positions(QUEEN, white));

  return pawn_attackers | knight_attackers | king_attackers | bishop_attackers | rook_attackers | queen_attackers;
}

// Check:
bool MoveGenerator::is_checked(Board* board, bool white) {
  bitboard king_position = board->get_piece_positions(KING, white);
  return get_attackers_to_position(board, king_position, !white);
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
