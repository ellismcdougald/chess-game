/*
 * Game class.
 */

class Game {
public:
  // Constructors:
  Game();

  // Game logic:
  void run_game(void);
  void do_turn(void);

  // Printers:
  void print_board(void);

  // Testing:
  void test_move_generator(void);

private:
  Board board;
  bool white_turn;
  MoveGenerator move_generator;

  // Helpers:
  bitboard generate_position(char col_letter, char row_number, bool white);
  void print_bitboard(bitboard bb);
};
  