#include "../src/cpu/instructions/instruction_step_op.hh"

#include "instructions_test.hh"
#include "mocks/mos_6510.hh"

#include <harpoon/c64-hw/cpu/mos_6510.hh>
#include <harpoon/execution/instruction.hh>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

class instruction_step_op : public instructions_test {
protected:
	c64::hw::cpu::instructions::instruction_step_op<mocks::mos_6510, std::uint8_t>
	    _instruction_step_op{&_mos_6510, &_instruction_step};
};

TEST_F(instruction_step_op, constructor) {
	std::uint8_t v;

	EXPECT_EQ(_instruction_step_op.get_cpu(), &_mos_6510);
	EXPECT_EQ(_instruction_step_op.get_instruction_step(), &_instruction_step);
}

class instruction_step_op_flags : public instruction_step_op,
                                  public ::testing::WithParamInterface<std::uint16_t> {};

TEST_P(instruction_step_op_flags, update_flag_Z) {
	std::uint8_t v = GetParam() & 0xFF;

	EXPECT_CALL(_mos_6510, set_flag_Z(v == 0));
	_instruction_step_op.update_flag_Z(v & 0xFF);
}

TEST_P(instruction_step_op_flags, update_flag_N) {
	std::uint8_t v = GetParam() & 0xFF;

	EXPECT_CALL(_mos_6510, set_flag_N((v & 0x80) == 0x80));
	_instruction_step_op.update_flag_N(v & 0xFF);
}

TEST_P(instruction_step_op_flags, update_flags_NZ) {
	std::uint8_t v = GetParam() & 0xFF;

	EXPECT_CALL(_mos_6510, set_flag_Z(v == 0));
	EXPECT_CALL(_mos_6510, set_flag_N((v & 0x80) == 0x80));
	_instruction_step_op.update_flags_NZ(v & 0xFF);
}

INSTANTIATE_TEST_SUITE_P(Full, instruction_step_op_flags, ::testing::Range<std::uint16_t>(0, 256));

} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
