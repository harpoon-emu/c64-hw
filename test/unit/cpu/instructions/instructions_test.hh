#ifndef TEST_UNIT_CPU_INSTRUCTIONS_INSTRUCTIONS_TEST_HH
#define TEST_UNIT_CPU_INSTRUCTIONS_INSTRUCTIONS_TEST_HH

#include "mocks/instruction_step.hh"
#include "mocks/memory.hh"
#include "mocks/mos_6510.hh"

#include <harpoon/execution/instruction.hh>

#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

class instructions_test : public ::testing::Test {
protected:
	virtual void SetUp();

	template<typename T>
	void _set_flags_expectations(bool f, T v) {
		if (f) {
			T h = 1 << (sizeof(T) * 8 - 1);
			EXPECT_CALL(_mos_6510, set_flag_N((v & h) == h));
			EXPECT_CALL(_mos_6510, set_flag_Z(v == 0));
		} else {
			EXPECT_CALL(_mos_6510, set_flag_N(::testing::_)).Times(0);
			EXPECT_CALL(_mos_6510, set_flag_Z(::testing::_)).Times(0);
		}
		EXPECT_CALL(_mos_6510, set_flag_C(::testing::_)).Times(0);
		EXPECT_CALL(_mos_6510, set_flag_I(::testing::_)).Times(0);
		EXPECT_CALL(_mos_6510, set_flag_D(::testing::_)).Times(0);
		EXPECT_CALL(_mos_6510, set_flag_V(::testing::_)).Times(0);
	}

	std::shared_ptr<mocks::memory> _memory{};
	mocks::mos_6510 _mos_6510{};
	harpoon::execution::instruction _instruction{
	    &_mos_6510, {}, [](const harpoon::execution::instruction &, std::ostream &) {}};
	mocks::instruction_step<mocks::mos_6510> _instruction_step{_instruction};
};


} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test

#endif
