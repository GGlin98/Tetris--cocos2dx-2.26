#include "Block.h"
#include <TetrisScene.h>

using std::array;

Block::Block(enum tag t = Block::BLOCK_NONE) : tag(t)
{
	if (t == Block::BLOCK_NONE)
		tag = static_cast<enum tag>(u(e));

	switch (tag)
	{
	case Block::BLOCK_I1: matrix = data[0]; break;
	case Block::BLOCK_I2: matrix = data[1]; break;
	case Block::BLOCK_I3: matrix = data[2]; break;
	case Block::BLOCK_I4: matrix = data[3]; break;
	case Block::BLOCK_J1: matrix = data[4]; break;
	case Block::BLOCK_J2: matrix = data[5]; break;
	case Block::BLOCK_J3: matrix = data[6]; break;
	case Block::BLOCK_J4: matrix = data[7]; break;
	case Block::BLOCK_L1: matrix = data[8]; break;
	case Block::BLOCK_L2: matrix = data[9]; break;
	case Block::BLOCK_L3: matrix = data[10]; break;
	case Block::BLOCK_L4: matrix = data[11]; break;
	case Block::BLOCK_O1: matrix = data[12]; break;
	case Block::BLOCK_O2: matrix = data[13]; break;
	case Block::BLOCK_O3: matrix = data[14]; break;
	case Block::BLOCK_O4: matrix = data[15]; break;
	case Block::BLOCK_S1: matrix = data[16]; break;
	case Block::BLOCK_S2: matrix = data[17]; break;
	case Block::BLOCK_S3: matrix = data[18]; break;
	case Block::BLOCK_S4: matrix = data[19]; break;
	case Block::BLOCK_T1: matrix = data[20]; break;
	case Block::BLOCK_T2: matrix = data[21]; break;
	case Block::BLOCK_T3: matrix = data[22]; break;
	case Block::BLOCK_T4: matrix = data[23]; break;
	case Block::BLOCK_Z1: matrix = data[24]; break;
	case Block::BLOCK_Z2: matrix = data[25]; break;
	case Block::BLOCK_Z3: matrix = data[26]; break;
	case Block::BLOCK_Z4: matrix = data[27]; break;
	default:
		exit(EXIT_FAILURE);
	}
}

Block::~Block(void)
{
}

const array<array<array<int, 4>, 4>, 28> Block::data = {
	// I1
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
	// I2
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// I3
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
	// I4
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// J1
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
	// J2
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 1,
			0, 0, 0, 0,
	// J3
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
	// J4
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
	// L1
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
	// L2
			0, 0, 0, 0,
			0, 1, 1, 1,
			0, 1, 0, 0,
			0, 0, 0, 0,
	// L3
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
	// L4
			0, 0, 0, 0,
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
	// O1
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// O2
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// O3
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// O4
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// S1
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// S2
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
	// S3
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// S4
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
	// T1
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// T2
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
	// T3
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// T4
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
	// Z1
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// Z2
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
	// Z3
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
	// Z4
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
};

std::default_random_engine Block::e(time(0));
std::uniform_int_distribution<unsigned> Block::u(1,28);
