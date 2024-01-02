enum piece {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE};
enum direction {NORTH, SOUTH, EAST, WEST, NORTHEAST, SOUTHEAST, NORTHWEST, SOUTHWEST};
typedef uint64_t bitboard;
#define RANK_1 0x00000000000000FF
#define RANK_8 0xFF00000000000000
#define FILE_H 0x0101010101010101
#define FILE_A 0x8080808080808080
#define NORTH(bb) (((bb) & ~(RANK_8)) << 8)
#define SOUTH(bb) (((bb) & ~(RANK_1)) >> 8)
#define WEST(bb) (((bb) & ~(FILE_A)) << 1)
#define EAST(bb) (((bb) & ~(FILE_H)) >> 1)
#define NORTHWEST(bb) (((bb) & ~(FILE_A) & ~(RANK_8)) << 9)
#define NORTHEAST(bb) (((bb) & ~(FILE_H) & ~(RANK_8)) << 7)
#define SOUTHWEST(bb) (((bb) & ~(FILE_A) & ~(RANK_1)) >> 7)
#define SOUTHEAST(bb) (((bb) & ~(FILE_H) & ~(RANK_1)) >> 9)
#define KNIGHT_NW_JUMP(bb) (WEST(NORTH(NORTH(bb))))
#define KNIGHT_NE_JUMP(bb) (EAST(NORTH(NORTH(bb))))
#define KNIGHT_SW_JUMP(bb) (WEST(SOUTH(SOUTH(bb))))
#define KNIGHT_SE_JUMP(bb) (EAST(SOUTH(SOUTH(bb))))
