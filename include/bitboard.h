#ifndef BITBOARD_H
#define BITBOARD_H

#include "definitons.h"

Uint64 add_in_position(Uint64 bitboard, int bit_pos) {
  return bitboard | (1ULL << bit_pos);
}

Uint64 get_mask(int bit_pos, Uint64 offset) { return ~(offset << bit_pos); };

Uint64 remove_piece(int bit_pos) {
  return gameData.bitboard & get_mask(bit_pos, 1ULL);
};

Uint64 check_in_position(Uint64 b, int bit_pos) {
  Uint64 bitboard = remove_piece(bit_pos);
  bitboard = add_in_position(b, bit_pos);

  if (bitboard != b)
    return -1;

  return 0;
}

Uint64 knight_shift(Uint64 b, int bit_pos, KnightDirection dir) {
  Uint64 bitboard = b;

  if (check_in_position(b, bit_pos) == -1) {
    printf("\n ERROR: Cannot shift the knight, no piece in position: %d \n\n",
           bit_pos);
    return b;
  }

  if (dir < 0)
    bitboard >>= -dir;

  else
    bitboard <<= dir;

  switch (dir) {
  case soSouthWest:
  case noNorthWest:
    return bitboard & notHFile;

  case weWestSouth:
  case weWestNorth:
    return bitboard & notGFile & notHFile;

  case eaEastNorth:
  case eaEastSouth:
    return bitboard & notBFile & notAFile;

  case noNorthEast:
  case soSouthEast:
    return bitboard & notAFile;
  }
}

Uint64 move_piece(Uint64 b, Player player, int bit_pos, Direction dir) {
  // Clear the bit

  if (check_in_position(b, bit_pos) == -1) {
    printf("\n ERROR: Cannot shift, no piece in position: %d \n\n", bit_pos);
    return b;
  }

  Uint64 bitboard = add_in_position(0ULL, bit_pos);

  if (player == black)
    dir *= -1;

  if (dir == north)
    return bitboard >>= 8 | b;

  else if (dir == south)
    return bitboard <<= 8 | b;

  // To prevent undesireble piece moviment
  if (dir < 0)
    bitboard >>= -dir;

  else
    bitboard <<= dir;

  if (dir == east || dir == northEast || dir == southEast)
    bitboard &= notAFile;

  else
    bitboard &= notHFile;

  return bitboard | b;
}

Uint64 piece_shift(Player player, int bit_pos, Direction dir) {
  // Clear the bit
  Uint64 bitboard = add_in_position(0ULL, bit_pos);

  if (player == black)
    dir *= -1;

  if (dir == north)
    return bitboard >>= 8;

  else if (dir == south)
    return bitboard <<= 8;

  // To prevent undesireble piece moviment
  if (dir < 0)
    bitboard >>= -dir;

  else
    bitboard <<= dir;

  if (dir == east || dir == northEast || dir == southEast)
    return bitboard & notAFile;

  return bitboard & notHFile;
}

Uint64 pawn_attacks_mask(Player player, int bit_pos) {
  Uint64 bitboard = add_in_position(0ULL, bit_pos);

  return move_piece(bitboard, player, bit_pos, northEast) |
         move_piece(bitboard, player, bit_pos, northWest);
}

Uint64 king_attacks_mask(int bit_pos) {
  Uint64 bitboard = add_in_position(0ULL, bit_pos);
  Player player = white;

  return move_piece(bitboard, player, bit_pos, north) |
         move_piece(bitboard, player, bit_pos, south) |
         move_piece(bitboard, player, bit_pos, northEast) |
         move_piece(bitboard, player, bit_pos, northWest) |
         move_piece(bitboard, player, bit_pos, southEast) |
         move_piece(bitboard, player, bit_pos, southWest) |
         move_piece(bitboard, player, bit_pos, east) |
         move_piece(bitboard, player, bit_pos, west);
}

void init_pawn_mask(int square) {
  pawn_attacks[white][square] = pawn_attacks_mask(white, square);
  pawn_attacks[black][square] = pawn_attacks_mask(black, square);
}

Uint64 pawn_move(int square, Player player) {
  Uint64 second_rank = 0xFF00;
  Uint64 seventh_rank = 0xFF000000000000;

  Uint64 bitboard = add_in_position(0ULL, square);

  if (((second_rank | seventh_rank) & bitboard) != 0) {

    bitboard = move_piece(bitboard, player, square, north);

    if (player == white)
      bitboard |= piece_shift(player, square - 8, north);

    else
      bitboard |= piece_shift(player, square + 8, north);

  } else
    bitboard = move_piece(bitboard, player, square, north);

  return bitboard;
}

void init_king_mask(int square) {
  king_attacks[square] = king_attacks_mask(square);
}

int get_rank(int square) { return square / 8; }

int get_file(int square) { return square % 8; }

Uint64 get_ray(int square, Direction dir) {
  int rank = get_rank(square);
  int file = get_file(square);

  int t_rank, t_file = 0;

  Uint64 ray = add_in_position(0ULL, square);

  switch (dir) {
  case southEast:
    // southEast ray
    for (t_file = file + 1, t_rank = rank + 1; t_file <= 7 && t_rank <= 7;
         t_file++, t_rank++) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // northWest ray
  case northWest:
    for (t_file = file - 1, t_rank = rank - 1; t_file >= 0 && t_rank >= 0;
         t_file--, t_rank--) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // southWest
  case southWest:
    for (t_file = file - 1, t_rank = rank + 1; t_file >= 0 && t_rank <= 7;
         t_file--, t_rank++) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // northEast
  case northEast:
    for (t_file = file + 1, t_rank = rank - 1; t_file <= 7 && t_rank >= 0;
         t_file++, t_rank--) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // north
  case north:
    for (t_file = file, t_rank = rank - 1; t_rank >= 0; t_rank--) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // south
  case south:
    for (t_file = file, t_rank = rank + 1; t_rank <= 7; t_rank++) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // east
  case east:
    for (t_file = file - 1, t_rank = rank; t_file >= 0; t_file--) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;

    // west
  case west:
    for (t_file = file + 1, t_rank = rank; t_file <= 7; t_file++) {
      int pos = t_rank * 8 + t_file;
      ray |= add_in_position(0ULL, pos);
    }
    break;
  }

  return ray ^ add_in_position(0ULL, square);
}

void init_bishop_mask(int square) {
  bishop_attacks[square] =
      get_ray(square, northEast) | get_ray(square, northWest) |
      get_ray(square, southEast) | get_ray(square, southWest);
}

void init_rook_mask(int square) {
  rook_attacks[square] = get_ray(square, north) | get_ray(square, south) |
                         get_ray(square, east) | get_ray(square, west);
}

void init_queen_attacks(int square) {
  queen_attacks[square] =
      get_ray(square, northEast) | get_ray(square, northWest) |
      get_ray(square, southEast) | get_ray(square, southWest) |
      get_ray(square, north) | get_ray(square, south) | get_ray(square, east) |
      get_ray(square, west);
}

void init_knight_attacks(int square) {
  Uint64 b = add_in_position(0ULL, square);

  knight_attacks[square] = knight_shift(b, square, noNorthWest) |
                         knight_shift(b, square, noNorthEast) |
                         knight_shift(b, square, soSouthWest) |
                         knight_shift(b, square, soSouthEast) |
                         knight_shift(b, square, eaEastNorth) |
                         knight_shift(b, square, eaEastSouth) |
                         knight_shift(b, square, weWestNorth) |
                         knight_shift(b, square, weWestSouth);
}

Uint64 get_valid_moves(Uint64 bitboard, int square);

void init_masks() {
  for (int square = 0; square < 64; square++) {
    init_pawn_mask(square);
    init_king_mask(square);
    init_bishop_mask(square);
    init_rook_mask(square);
    init_queen_attacks(square);
    init_knight_attacks(square);
  }
}

void print_bitboard(Uint64 bitboard) {
  printf("   ");
  for (int i = 'a'; i < 'a' + 8; i++)
    printf(" %c", i);

  printf("\n");

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      // Calculate square with the coordinates
      int square = rank * 8 + file;

      // if (rank == 6)
      //   printf("1");
      // else
      //   printf("0");

      if (!file)
        printf(" %d ", 8 - rank);

      printf(" %c", (bitboard & (1ULL << square)) ? '1' : '0');
    }
    printf("\n");
  }
}

#endif
