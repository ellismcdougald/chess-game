/*
 * Game definitions.
 */

#pragma once

#include"Game.hpp"

// Constructors:
Game::Game() : board(false) {
  white_turn = true;
}

// Game Logic:
void Game::run_game(void) {
  while(true) {
    do_turn();
    // TODO: break for checkmate or stalemate
  }
}

void Game::do_turn(void) {
  std::cout << (white_turn ? "White" : "Black") << ": It is your turn.\n";
  board.print_board();

  Move move = query_legal_move();

  update_castle_permissions(&move);
  
  board.execute_move(&move);

  board.print_board();

  white_turn = !white_turn;
}

Move Game::query_legal_move(void) {
  bool move_is_legal = false;
  while(!move_is_legal) {
    char start_row, start_col, end_row, end_col;

    std::cout << "Start position (i.e. d2): ";
    std::cin >> start_col >> start_row;
    std::cout << "End position (i.e. d4): ";
    std::cin >> end_col >> end_row;
    
    bitboard start_position = generate_position(start_col, start_row, white_turn);
    bitboard end_position = generate_position(end_col, end_row, white_turn);
    
    piece move_piece = board.get_piece_at_position(start_position, white_turn);
    piece capture_piece = board.get_piece_at_position(end_position, !white_turn);

    bool castle = start_position == 0x8 && (end_position == 0x80 || end_position == 1)
      && move_piece == KING &&
      board.get_piece_at_position(end_position, white_turn) == ROOK;
    
    Move move(white_turn, start_position, end_position, move_piece, capture_piece, castle);

    std::vector<Move> legal_moves = move_generator.generate_legal_moves(&board, white_turn);
    for(int i = 0; i < legal_moves.size(); i++) {
      legal_moves[i].print_move();
    }

    move_is_legal = is_move_legal(legal_moves, &move);
    move_is_legal = true;
    if(!move_is_legal) {
      std::cout << "Illegal move. Try again.\n";
    } else {
      return move;
    }
  }
  
  return Move(0, 0, 0, NONE, NONE, 0);
}

// Printers:
void Game::print_board(void) {
  board.print_board();
}

// Getters:
Board* Game::get_board_ptr(void) {
  return &board;
}

MoveGenerator* Game::get_move_generator_ptr(void) {
  return &move_generator;
}

// Helpers:
bitboard Game::generate_position(char col_letter, char row_number, bool white) {
  char col_number = col_letter - 97 + 1;
  if(white) {
    return (bitboard) 1 << (8 - col_number) << (row_number - 1) * 8;
  } else {
    return (bitboard) 1 << (8 - col_number) << (8 - row_number) * 8;
  }
}

void Game::print_bitboard(bitboard bb) {
  bitboard mask = (bitboard) 1 << 63;
  for(int i = 0; i < 64; i++) {
    std::cout << (mask & bb ? 1 : 0);
    mask >>= 1;
    if((i + 1) % 8 == 0) std::cout << "\n";
  }
}

bool Game::is_move_legal(std::vector<Move> legal_moves, Move* move) {
  for(int i = 0; i < legal_moves.size(); i++) {
    if(move->move_equals(&legal_moves[i])) return true;
  }
  return false;
}

// Testing:
void Game::test_move_generator(void) {
  std::cout << "Testing move generator\n";

  Move move(true, generate_position('d', 2, true), generate_position('d', 4, true), PAWN, NONE, false);
  board.execute_move(&move);
  Move move_1(true, generate_position('e', 2, true), generate_position('e', 4, true), PAWN, NONE, false);
  board.execute_move(&move_1);
  board.print_board();
  
  move_generator.generate_king_pseudo_legal_moves(&board, true);
}

void Game::update_castle_permissions(Move *move) {
  if(move->get_move_piece() == KING) {
    if(white_turn) {
      move_generator.set_white_can_castle_left(false);
      move_generator.set_white_can_castle_right(false);
    } else {
      move_generator.set_black_can_castle_left(false);
      move_generator.set_black_can_castle_right(false);
    }
  } else if(move->get_move_piece() == ROOK) {
    if(move->get_start_position() == (bitboard) 1) {
      if(white_turn) {
	move_generator.set_white_can_castle_right(false);
      } else {
	move_generator.set_black_can_castle_right(false);
      }
    } else if(move->get_start_position() == (bitboard) 0x80) {
      if(white_turn) {
	move_generator.set_white_can_castle_left(false);
      } else {
	move_generator.set_black_can_castle_left(false);
      }
    }
  }
}
