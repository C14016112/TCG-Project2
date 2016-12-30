#ifndef __FIB2584BITBOARD_H__
#define __FIB2584BITBOARD_H__
#include <iostream>
#pragma once
class Fib2584BitBoard
{
private:
	unsigned long long int  left_; // upper board, use 40 bit
	unsigned long long int  right_; // down board, use 40 bit
	static const Fib2584BitBoard static_legal_mask;
public:
	Fib2584BitBoard();
	~Fib2584BitBoard();
	Fib2584BitBoard(unsigned long long int right);
	Fib2584BitBoard(unsigned long long int left, unsigned long long int right);
	unsigned long long get_right() { return right_; };
	operator int();
	Fib2584BitBoard& operator=(const unsigned long long& right);
	Fib2584BitBoard& operator=(const Fib2584BitBoard bitboard);
	bool operator==(const Fib2584BitBoard& bit_board);
	bool operator==(const int& right);
	bool operator!=(const Fib2584BitBoard& bit_board);
	bool operator!=(const int& right);
	Fib2584BitBoard operator<<(const int& shift_num);
	Fib2584BitBoard& operator<<=(const int& shift_num);
	Fib2584BitBoard operator>>(const int& shift_num);
	Fib2584BitBoard& operator>>=(const int& shift_num);
	Fib2584BitBoard operator&(const Fib2584BitBoard& bit_board) const;
	Fib2584BitBoard operator&(const int& right) const;
	Fib2584BitBoard& operator&=(const Fib2584BitBoard& bit_board);
	Fib2584BitBoard& operator&=(const int& right);
	Fib2584BitBoard operator|(const Fib2584BitBoard& bit_board);
	Fib2584BitBoard& operator|=(const Fib2584BitBoard& bit_board);
	Fib2584BitBoard operator~();
	void show();

};


#endif