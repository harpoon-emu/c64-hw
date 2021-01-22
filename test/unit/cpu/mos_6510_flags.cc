#include <harpoon/c64-hw/cpu/mos_6510_flags.hh>

#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {

class mos_6510_flags : public ::testing::Test {
protected:
	virtual void SetUp() {
		_flags.set_flags(0);
	}

	c64::hw::cpu::mos_6510_flags _flags{};
};

TEST_F(mos_6510_flags, all_0) {
	_flags.set_flags(0);
	EXPECT_FALSE(_flags.C());
	EXPECT_FALSE(_flags.Z());
	EXPECT_FALSE(_flags.I());
	EXPECT_FALSE(_flags.D());
	EXPECT_FALSE(_flags.B());
	EXPECT_FALSE(_flags.V());
	EXPECT_FALSE(_flags.N());
}

TEST_F(mos_6510_flags, all_1) {
	_flags.set_flags(0xFF);
	EXPECT_TRUE(_flags.C());
	EXPECT_TRUE(_flags.Z());
	EXPECT_TRUE(_flags.I());
	EXPECT_TRUE(_flags.D());
	EXPECT_TRUE(_flags.B());
	EXPECT_TRUE(_flags.V());
	EXPECT_TRUE(_flags.N());
}

TEST_F(mos_6510_flags, C_set) {
	_flags.C() = true;
	EXPECT_TRUE(_flags.C());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x01);
}

TEST_F(mos_6510_flags, C_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.C() = false;
	EXPECT_FALSE(_flags.C());
	EXPECT_EQ(_flags.get_flags(), f & ~0x01);
}

TEST_F(mos_6510_flags, Z_set) {
	_flags.Z() = true;
	EXPECT_TRUE(_flags.Z());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x02);
}

TEST_F(mos_6510_flags, Z_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.Z() = false;
	EXPECT_FALSE(_flags.Z());
	EXPECT_EQ(_flags.get_flags(), f & ~0x02);
}

TEST_F(mos_6510_flags, I_set) {
	_flags.I() = true;
	EXPECT_TRUE(_flags.I());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x04);
}

TEST_F(mos_6510_flags, I_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.I() = false;
	EXPECT_FALSE(_flags.I());
	EXPECT_EQ(_flags.get_flags(), f & ~0x04);
}

TEST_F(mos_6510_flags, D_set) {
	_flags.D() = true;
	EXPECT_TRUE(_flags.D());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x08);
}

TEST_F(mos_6510_flags, D_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.D() = false;
	EXPECT_FALSE(_flags.D());
	EXPECT_EQ(_flags.get_flags(), f & ~0x08);
}

TEST_F(mos_6510_flags, B_set) {
	_flags.B() = true;
	EXPECT_TRUE(_flags.B());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x10);
}

TEST_F(mos_6510_flags, B_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.B() = false;
	EXPECT_FALSE(_flags.B());
	EXPECT_EQ(_flags.get_flags(), f & ~0x10);
}

TEST_F(mos_6510_flags, V_set) {
	_flags.V() = true;
	EXPECT_TRUE(_flags.V());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x40);
}

TEST_F(mos_6510_flags, V_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.V() = false;
	EXPECT_FALSE(_flags.V());
	EXPECT_EQ(_flags.get_flags(), f & ~0x40);
}

TEST_F(mos_6510_flags, N_set) {
	_flags.N() = true;
	EXPECT_TRUE(_flags.N());
	EXPECT_EQ(_flags.get_flags() & ~0x20, 0x80);
}

TEST_F(mos_6510_flags, N_clear) {
	_flags.set_flags(0xFF);
	uint8_t f = _flags.get_flags();

	_flags.N() = false;
	EXPECT_FALSE(_flags.N());
	EXPECT_EQ(_flags.get_flags(), f & ~0x80);
}

TEST_F(mos_6510_flags, unused_set) {
	uint8_t f = _flags.get_flags();
	_flags.set_flags(f | 0x20);
	EXPECT_EQ(_flags.get_flags(), f);
}

TEST_F(mos_6510_flags, unused_clear) {
	uint8_t f = _flags.get_flags();
	_flags.set_flags(f & ~0x20);
	EXPECT_EQ(_flags.get_flags(), f);
}

} // namespace cpu
} // namespace unit
} // namespace test