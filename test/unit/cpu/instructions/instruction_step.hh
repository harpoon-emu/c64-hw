#include "instructions_test.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

template<typename C>
class instruction_step_test : public instructions_test {
protected:
	C _instruction_step_ut{_instruction};

	void test_check(std::uint32_t expect = 0) {
		EXPECT_EQ(_instruction_step_ut.check(), expect);
	}

	void test_step(std::uint32_t expect_add = 0) {
		_instruction_step_ut.set_delay(128);
		EXPECT_EQ(_instruction_step_ut.step(), 128 + expect_add);
	}
};

} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
