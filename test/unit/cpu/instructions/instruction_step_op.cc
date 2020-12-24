#include "../src/cpu/instructions/instruction_step_op.hh"

#include "../src/cpu/instructions/instruction_step.hh"

#include <harpoon/c64-hw/cpu/mos_6510.hh>
#include <harpoon/execution/instruction.hh>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

namespace mocks {
class mos_6510 : public c64::hw::cpu::mos_6510 {
public:
	MOCK_METHOD(void, set_flag_N, (bool), ());
	MOCK_METHOD(void, set_flag_Z, (bool), ());
};

template<typename CPU>
class instruction_step : public c64::hw::cpu::instructions::instruction_step<CPU> {
public:
	using c64::hw::cpu::instructions::instruction_step<CPU>::instruction_step;

	MOCK_METHOD(std::uint32_t, check, (), (override));
	MOCK_METHOD(void, execute, (), (override));
};

} // namespace mocks

class instruction_step_op : public ::testing::Test {
protected:
	mocks::mos_6510 _mos_6510{};
	harpoon::execution::instruction _instruction{
	    &_mos_6510, {}, [](const harpoon::execution::instruction &, std::ostream &) {}};
	mocks::instruction_step<mocks::mos_6510> _step{_instruction};
	c64::hw::cpu::instructions::instruction_step_op<mocks::mos_6510, std::uint8_t> _step_op{
	    &_mos_6510, &_step};
};

TEST_F(instruction_step_op, constructor) {
	std::uint8_t v;

	EXPECT_EQ(_step_op.get_cpu(), &_mos_6510);
	EXPECT_EQ(_step_op.get_instruction_step(), &_step);
}

class instruction_step_op_flags : public instruction_step_op,
                                  public ::testing::WithParamInterface<std::uint16_t> {};

TEST_P(instruction_step_op_flags, update_flag_Z) {
	std::uint8_t v = GetParam() & 0xFF;

	EXPECT_CALL(_mos_6510, set_flag_Z(v == 0));
	_step_op.update_flag_Z(v & 0xFF);
}

TEST_P(instruction_step_op_flags, update_flag_N) {
	std::uint8_t v = GetParam() & 0xFF;

	EXPECT_CALL(_mos_6510, set_flag_N((v & 0x80) == 0x80));
	_step_op.update_flag_N(v & 0xFF);
}

TEST_P(instruction_step_op_flags, update_flags_NZ) {
	std::uint8_t v = GetParam() & 0xFF;

	EXPECT_CALL(_mos_6510, set_flag_Z(v == 0));
	EXPECT_CALL(_mos_6510, set_flag_N((v & 0x80) == 0x80));
	_step_op.update_flags_NZ(v & 0xFF);
}

INSTANTIATE_TEST_SUITE_P(Full, instruction_step_op_flags, ::testing::Range<std::uint16_t>(0, 256));

} // namespace