/*
 * LookupTables implementation.
 */

#pragma once

#include"LookupTables.hpp"

// Constructors:
LookupTables::LookupTables(void) {
  initialize_king_move_lookup_table();
  initialize_knight_move_lookup_table();
  initialize_pawn_single_push_lookup_table();
  initialize_pawn_double_push_lookup_table();
  initialize_pawn_attack_lookup_table();
}

// Getters:
bitboard LookupTables::get_king_move_bitboard(bitboard position) {
  return king_move_lookup_table[position];
}

bitboard LookupTables::get_knight_move_bitboard(bitboard position) {
  return knight_move_lookup_table[position];
}

bitboard LookupTables::get_pawn_single_push_bitboard(bitboard position) {
  return pawn_single_push_lookup_table[position];
}

bitboard LookupTables::get_pawn_double_push_bitboard(bitboard position) {
  return pawn_double_push_lookup_table[position];
}

bitboard LookupTables::get_pawn_attack_bitboard(bitboard position) {
  return pawn_attack_lookup_table[position];
}

// Initializers:
void LookupTables::initialize_king_move_lookup_table(void) {
  for(bitboard position = 1; position > 0; position <<= 1) {
    king_move_lookup_table[position] = NORTH(position) | SOUTH(position) | WEST(position) |
      EAST(position) | NORTHWEST(position) | NORTHEAST(position) | SOUTHWEST(position) |
      SOUTHEAST(position);
  }
}

void LookupTables::initialize_knight_move_lookup_table(void) {
  for(bitboard position = 1; position > 0; position <<= 1) {
    knight_move_lookup_table[position] = KNIGHT_NW_JUMP(position) | KNIGHT_NE_JUMP(position) | KNIGHT_SW_JUMP(position) | KNIGHT_SE_JUMP(position);
  }
}

void LookupTables::initialize_pawn_single_push_lookup_table(void) {
  for(bitboard position = 1; position > 0; position <<= 1) {
    pawn_single_push_lookup_table[position] = NORTH(position);
  }
}

void LookupTables::initialize_pawn_double_push_lookup_table(void) {
  for(bitboard position = 1; position > 0; position <<= 1) {
    if(position >= 0x100 && position < 0x10000) {
      pawn_double_push_lookup_table[position] = NORTH(NORTH(position));
    } else {
      pawn_double_push_lookup_table[position] = 0;
    }
  }
}

void LookupTables::initialize_pawn_attack_lookup_table(void) {
  for(bitboard position = 1; position > 0; position <<= 1) {
    pawn_attack_lookup_table[position] = NORTHWEST(position) | NORTHEAST(position);
  }
}



