/*
 * LookupTables implementation.
 */

#pragma once

#include"LookupTables.hpp"

// Constructors:
LookupTables::LookupTables(void) {
  initialize_king_move_lookup_table();
}

// Getters:
bitboard LookupTables::get_king_move_bitboard(bitboard position) {
  return king_move_lookup_table[position];
}

// Initializers:
void LookupTables::initialize_king_move_lookup_table(void) {
  bitboard result;
  for(bitboard position = 1; position > 0; position <<= 1) {
    king_move_lookup_table[position] = NORTH(position) | SOUTH(position) | WEST(position) |
      EAST(position) | NORTHWEST(position) | NORTHEAST(position) | SOUTHWEST(position) |
      SOUTHEAST(position);
  }
}



