#pragma once
#include <array>
#include <random>
#include <ctime>
#include <utility>

using std::array;
using std::pair;

class Block
{
public:
	enum tag { 
		BLOCK_I1 = 1, BLOCK_I2, BLOCK_I3, BLOCK_I4,
		BLOCK_J1, BLOCK_J2, BLOCK_J3, BLOCK_J4,
		BLOCK_L1, BLOCK_L2, BLOCK_L3, BLOCK_L4,
		BLOCK_O1, BLOCK_O2, BLOCK_O3, BLOCK_O4,
		BLOCK_S1, BLOCK_S2, BLOCK_S3, BLOCK_S4,
		BLOCK_T1, BLOCK_T2, BLOCK_T3, BLOCK_T4,
		BLOCK_Z1, BLOCK_Z2, BLOCK_Z3, BLOCK_Z4,
		BLOCK_NONE
	} tag;
	
	array<array<int, 4>, 4> matrix;

	pair<int, int> posOfNextBlock;

	Block(enum tag t);

	~Block(void);

private:
	static const array<array<array<int, 4>, 4>, 28> data;
	static const array<array<int, 2>, 28> posOfNextBlockData;
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u;
};

