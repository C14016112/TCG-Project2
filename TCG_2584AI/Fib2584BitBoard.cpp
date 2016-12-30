#include "Fib2584BitBoard.h"
using namespace std;
const Fib2584BitBoard Fib2584BitBoard::static_legal_mask = Fib2584BitBoard(0x000000ffffffffff, 0x000000ffffffffff);

Fib2584BitBoard::Fib2584BitBoard() :
	left_(0),
	right_(0)
{
}

Fib2584BitBoard::Fib2584BitBoard(unsigned long long right) :
	left_(0),
	right_(right)
{
}

Fib2584BitBoard::Fib2584BitBoard(unsigned long long left, unsigned long long right) :
	left_(left),
	right_(right)
{
	left_ &= static_legal_mask.left_;
}

Fib2584BitBoard::~Fib2584BitBoard()
{
}

Fib2584BitBoard::operator int()
{
	return right_;
}

Fib2584BitBoard& Fib2584BitBoard::operator=(const unsigned long long& right)
{
	left_ = 0;
	right_ = right;
	return *this;
}

Fib2584BitBoard& Fib2584BitBoard::operator=(const Fib2584BitBoard bitboard)
{
	left_ = bitboard.left_;
	right_ = bitboard.right_;
	return *this;
}

bool Fib2584BitBoard::operator==(const Fib2584BitBoard& bit_board)
{
	return left_ == bit_board.left_ && right_ == bit_board.right_;
}

bool Fib2584BitBoard::operator==(const int& right)
{
	return left_ == 0 && right_ == right;
}

bool Fib2584BitBoard::operator!=(const Fib2584BitBoard& bit_board)
{
	return left_ != bit_board.left_ || right_ != bit_board.right_;
}

bool Fib2584BitBoard::operator!=(const int& right)
{
	return left_ != 0 || right_ != right;
}

Fib2584BitBoard Fib2584BitBoard::operator<<(const int& shift_num)
{
	if (shift_num == 0)
		return *this;
	Fib2584BitBoard result = *this;
	if (shift_num < 40) {
		result.left_ <<= shift_num;
		result.left_ |= right_ >> (40 - shift_num);
		result.right_ <<= shift_num;
	}
	else {
		result.left_ = right_ << (shift_num - 40);
		result.right_ = 0;
	}
	result.left_ &= static_legal_mask.left_;
	return result;
}

Fib2584BitBoard& Fib2584BitBoard::operator<<=(const int& shift_num)
{
	if (shift_num == 0)
		return *this;
	if (shift_num < 40) {
		left_ <<= shift_num;
		left_ |= right_ >> (40 - shift_num);
		right_ <<= shift_num;
	}
	else {
		left_ = right_ << (shift_num - 40);
		right_ = 0;
	}
	left_ &= static_legal_mask.left_;
	return *this;
}

Fib2584BitBoard Fib2584BitBoard::operator>>(const int& shift_num)
{
	if (shift_num == 0)
		return *this;
	Fib2584BitBoard result = *this;
	if (shift_num < 40) {
		result.right_ >>= shift_num;
		result.right_ |= left_ << (40 - shift_num);
		result.left_ >>= shift_num;
	}
	else {
		result.right_ = left_ >> (shift_num - 40);
		result.left_ = 0;
	}
	return result;
}

Fib2584BitBoard& Fib2584BitBoard::operator>>=(const int& shift_num)
{
	if (shift_num == 0)
		return *this;
	right_ >>= shift_num;
	if (shift_num < 40) {
		right_ |= left_ << (40 - shift_num);
		left_ >>= shift_num;
	}
	else {
		right_ = left_ >> (shift_num - 40);
		left_ = 0;
	}
	return *this;
}

Fib2584BitBoard Fib2584BitBoard::operator&(const Fib2584BitBoard& bit_board) const
{
	return Fib2584BitBoard(left_ & bit_board.left_, right_ & bit_board.right_);
}

Fib2584BitBoard Fib2584BitBoard::operator&(const int& right) const
{
	return Fib2584BitBoard(left_ & 0, right_ & right);
}

Fib2584BitBoard& Fib2584BitBoard::operator&=(const Fib2584BitBoard& bit_board)
{
	left_ &= bit_board.left_;
	right_ &= bit_board.right_;
	return *this;
}

Fib2584BitBoard& Fib2584BitBoard::operator&=(const int& right)
{
	left_ &= 0;
	right_ &= right;
	return *this;
}

Fib2584BitBoard Fib2584BitBoard::operator|(const Fib2584BitBoard& bit_board)
{
	return Fib2584BitBoard(left_ | bit_board.left_, right_ | bit_board.right_);
}

Fib2584BitBoard& Fib2584BitBoard::operator|=(const Fib2584BitBoard& bit_board)
{
	left_ |= bit_board.left_;
	right_ |= bit_board.right_;
	return *this;
}

Fib2584BitBoard Fib2584BitBoard::operator~()
{
	return Fib2584BitBoard(~left_, ~right_);
}

void Fib2584BitBoard::show()
{
	cout << "left: " << hex << left_ << endl;
	cout << "right: " << hex << right_ << endl;
}
