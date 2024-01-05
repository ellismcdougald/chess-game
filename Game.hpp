/*
 * Game class.
 */

class Game {
public:
  // Constructors:
  Game();

  // Game logic:
  void run_game(void);
  bool do_turn(void);
  Move query_legal_move(std::vector<Move> legal_moves);

  // Printers:
  void print_board(void);

  // Testing:
  void test_move_generator(void);

  // Getters
  Board* get_board_ptr(void);
  MoveGenerator* get_move_generator_ptr(void);

private:
  Board board;
  bool white_turn;
  MoveGenerator move_generator;

  // Helpers:
  bitboard generate_position(char col_letter, char row_number, bool white);
  void print_bitboard(bitboard bb);
  bool is_move_legal(std::vector<Move> legal_moves, Move* move);
  void update_castle_permissions(Move *move);
};
  
