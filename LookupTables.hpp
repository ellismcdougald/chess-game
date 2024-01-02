/*
 * LookupTables class.
 */

#pragma once

class LookupTables {
public:
  // Constructors:
  LookupTables(void);

  // Getters
  bitboard get_king_move_bitboard(bitboard position);
  bitboard get_knight_move_bitboard(bitboard position);
  bitboard get_pawn_single_push_bitboard(bitboard position);
  bitboard get_pawn_double_push_bitboard(bitboard position);
  bitboard get_pawn_attack_bitboard(bitboard position);

private:
  // Lookup Tables:
  std::map<bitboard, bitboard> king_move_lookup_table;
  std::map<bitboard, bitboard> knight_move_lookup_table;
  std::map<bitboard, bitboard> pawn_single_push_lookup_table;
  std::map<bitboard, bitboard> pawn_double_push_lookup_table;
  std::map<bitboard, bitboard> pawn_attack_lookup_table;
  
  // Initializers:
  void initialize_king_move_lookup_table(void);
  void initialize_knight_move_lookup_table(void);
  void initialize_pawn_single_push_lookup_table(void);
  void initialize_pawn_double_push_lookup_table(void);
  void initialize_pawn_attack_lookup_table(void);
};
