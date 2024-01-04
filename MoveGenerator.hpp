/*
 * MoveGenerator class.
 */

#pragma once

class MoveGenerator {
public:
  MoveGenerator();

  // Legal moves:
  bool is_move_legal(Move* move, Board* board);
  std::vector<Move> generate_legal_moves(Board* board, bool white); // TODO

  // Pseudo-legal move generation:
  std::vector<Move> generate_piece_pseudo_legal_moves(Board* board, bool white, piece move_piece);
  
  std::vector<Move> generate_king_pseudo_legal_moves(Board* board, bool white);
  std::vector<Move> generate_queen_pseudo_legal_moves(Board* board, bool white); // TODO
  std::vector<Move> generate_rook_pseudo_legal_moves(Board* board, bool white); // TODO
  std::vector<Move> generate_bishop_pseudo_legal_moves(Board* board, bool white); // TODO
  std::vector<Move> generate_knight_pseudo_legal_moves(Board* board, bool white); // TODO
  std::vector<Move> generate_pawn_pseudo_legal_moves(Board* board, bool white); // TODO

  // King Moves:
  std::vector<Move> generate_castle_moves(); // TODO
  std::vector<Move> generate_evasion_moves(Board* board, bool white); // IN PROGRESS

  

  // Sliding Piece Moves
  bitboard generate_sliding_piece_move_table(direction slide_direction, bitboard piece_position, bitboard other_piece_positions, bitboard opponent_piece_positions);
  
  // Move tables:
  bitboard generate_king_move_table(bitboard king_position, bitboard other_piece_positions);
  bitboard generate_pawn_move_table(bitboard pawn_position, bitboard other_piece_positions, bitboard opponent_piece_positions);
  bitboard generate_knight_move_table(bitboard knight_position, bitboard other_piece_positions);
  bitboard generate_queen_move_table(bitboard queen_position, bitboard other_piece_positions, bitboard opponent_piece_positions);
  bitboard generate_rook_move_table(bitboard rook_position, bitboard other_piece_positions, bitboard opponent_piece_positions);
  bitboard generate_bishop_move_table(bitboard bishop_position, bitboard other_piece_positions, bitboard opponent_piece_positions);
  bitboard get_move_table_by_piece(piece move_piece, bitboard position, bitboard other_piece_positions, bitboard opponent_piece_positions);

  // Threat Tables:
  bitboard generate_threat_table(Board *board, bool white, bool exclude_king); // TODO
  bitboard get_threats_by_piece(piece piece, Board *board, bitboard position, bool white, bool exclude_king);
  bitboard get_attackers_to_position(Board *board, bitboard position, bool white);
  std::array<bitboard, 6> get_attackers_to_position_by_piece(Board *board, bitboard position, bool white);

  // Check:
  bool is_checked(Board* board, bool white);

private:
  LookupTables lookup_tables;

  // Print:
  void print_bitboard(bitboard bb);

  // Helpers:
  bitboard move_direction(direction move_direction, bitboard position);
  int count_attackers(std::array<bitboard, 6> attackers_by_position);
  int count_bits(bitboard bb);

};
