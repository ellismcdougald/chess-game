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

private:
  // Lookup Tables:
  std::map<bitboard, bitboard> king_move_lookup_table;

  // Initializers:
  void initialize_king_move_lookup_table(void);
};
