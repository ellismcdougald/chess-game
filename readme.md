# Command Line Chess

## Description:

This is a two-player chess game played in the command line. It queries players for moves, checks that they are legal, then executes them on the board.

## Usage:

1. Clone this repository
2. Compile with `g++ main.cpp`
3. Run the program with `./a.out`

## Example Game:

```
White: It is your turn.
8  r | n | b | q | k | b | n | r
  -------------------------------
7  p | p | p | p | p | p | p | p
  -------------------------------
6    |   |   |   |   |   |   |
  -------------------------------
5    |   |   |   |   |   |   |
  -------------------------------
4    |   |   |   |   |   |   |
  -------------------------------
3    |   |   |   |   |   |   |
  -------------------------------
2  P | P | P | P | P | P | P | P
  -------------------------------
1  R | N | B | Q | K | B | N | R
  -------------------------------
   A   B   C   D   E   F   G   H
Start position (i.e. d2): f2
End position (i.e. d4): f3

Black: It is your turn.
8  r | n | b | q | k | b | n | r
  -------------------------------
7  p | p | p | p | p | p | p | p
  -------------------------------
6    |   |   |   |   |   |   |
  -------------------------------
5    |   |   |   |   |   |   |
  -------------------------------
4    |   |   |   |   |   |   |
  -------------------------------
3    |   |   |   |   | P |   |
  -------------------------------
2  P | P | P | P | P |   | P | P
  -------------------------------
1  R | N | B | Q | K | B | N | R
  -------------------------------
   A   B   C   D   E   F   G   H
Start position (i.e. d2): e7
End position (i.e. d4): e5

White: It is your turn.
8  r | n | b | q | k | b | n | r
  -------------------------------
7  p | p | p | p |   | p | p | p
  -------------------------------
6    |   |   |   |   |   |   |
  -------------------------------
5    |   |   |   | p |   |   |
  -------------------------------
4    |   |   |   |   |   |   |
  -------------------------------
3    |   |   |   |   | P |   |
  -------------------------------
2  P | P | P | P | P |   | P | P
  -------------------------------
1  R | N | B | Q | K | B | N | R
  -------------------------------
   A   B   C   D   E   F   G   H
Start position (i.e. d2): g2
End position (i.e. d4): g4

Black: It is your turn.
8  r | n | b | q | k | b | n | r
  -------------------------------
7  p | p | p | p |   | p | p | p
  -------------------------------
6    |   |   |   |   |   |   |
  -------------------------------
5    |   |   |   | p |   |   |
  -------------------------------
4    |   |   |   |   |   | P |
  -------------------------------
3    |   |   |   |   | P |   |
  -------------------------------
2  P | P | P | P | P |   |   | P
  -------------------------------
1  R | N | B | Q | K | B | N | R
  -------------------------------
   A   B   C   D   E   F   G   H
Start position (i.e. d2): d8
End position (i.e. d4): h4

White: It is your turn.
8  r | n | b |   | k | b | n | r
  -------------------------------
7  p | p | p | p |   | p | p | p
  -------------------------------
6    |   |   |   |   |   |   |
  -------------------------------
5    |   |   |   | p |   |   |
  -------------------------------
4    |   |   |   |   |   | P | q
  -------------------------------
3    |   |   |   |   | P |   |
  -------------------------------
2  P | P | P | P | P |   |   | P
  -------------------------------
1  R | N | B | Q | K | B | N | R
  -------------------------------
   A   B   C   D   E   F   G   H

Checkmate! Black wins!
```

## Future Steps:

### Improvements:

- Implement en passant moves
- Fully test move generation
- Add Universal Chess Interface support

I also hope that this will serve as the foundation for a fully-fledged chess engine. In its current form, this project implements move generation, which is one of the the three key components of a chess engine. I hope to build upon this to implement the other two components-- evaluation and search-- in the future.

### Chess engine next steps:

- Optimize move generation for better performance
- Implement evaluation
- Implement search
