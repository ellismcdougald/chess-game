/*
 * Board class.
 */

class Board {
public:
  // Constructors:
  Board(bool empty);

  // Getters:
  bitboard get_piece_positions(piece p, bool white);

  // Printers:
  void print_board(void);
  void print_piece_positions(piece p, bool white);

  // Board management:
  void set_piece_position(bitboard position, piece p, bool white);
  void clear_piece_position(bitboard position, piece p, bool white);

  // Moves:
  void execute_move(Move *move);
  void undo_move(Move *move);
  
private:
  bitboard white_bitboards[6];
  bitboard black_bitboards[6];

  // Initializers
  void initialize_starting_position(void);

  // Print
  void print_bitboard(bitboard bitboard);

  // Helpers
  piece get_piece_at_position(bitboard position, bool white);
  piece get_piece_from_index(int piece_index);
  char get_char_from_piece(piece p);
};
