#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include "Fib2584/MoveDirection.h"
#include "assert.h"
#include "math.h"
#define iUpperbound 22
const int upsidedown_table[16] = {3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12};
const int rotate_table[16] = {3, 7, 11, 15, 2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12};

int GetFibOrder(int Fibnumber);
bool isEmpty(int board[4][4]);
bool isFull(int board[4][4]);
int GetMaxTile(int board[4][4]);
int pow(int x, int y);
#endif