#ifndef TEST_UNIT_CPU_INSTRUCTIONS_INSTRUCTIONS_TEST_HH
#define TEST_UNIT_CPU_INSTRUCTIONS_INSTRUCTIONS_TEST_HH

#include "mocks/instruction_step.hh"
#include "mocks/mos_6510.hh"

#include <harpoon/execution/instruction.hh>

#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

class instructions_test : public ::testing::Test {
protected:
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
