#include "../src/cpu/instructions/cpu_accessor.hh"

#include "instructions_test.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

class cpu_accessor : public instructions_test {};

#define ACCESSOR_TESTS(REG)                                                                \
	TEST_F(cpu_accessor, REG##_set) {                                                      \
		c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510> r(&_mos_6510,          \
		                                                              &_instruction_step); \
                                                                                           \
		EXPECT_CALL(_mos_6510, set_##REG(0xAA));                                           \
		r.set(0xAA);                                                                       \
	}                                                                                      \
                                                                                           \
	TEST_F(cpu_accessor, REG##_get) {                                                      \
		c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510> r(&_mos_6510,          \
		                                                              &_instruction_step); \
                                                                                           \
		EXPECT_CALL(_mos_6510, get_##REG());                                               \
		r.get();                                                                           \
	}

ACCESSOR_TESTS(A)
ACCESSOR_TESTS(X)
ACCESSOR_TESTS(Y)

ACCESSOR_TESTS(SP)

ACCESSOR_TESTS(PC)
ACCESSOR_TESTS(PCL)
ACCESSOR_TESTS(PCH)

ACCESSOR_TESTS(latch)

ACCESSOR_TESTS(P)
ACCESSOR_TESTS(flag_N)
ACCESSOR_TESTS(flag_Z)
ACCESSOR_TESTS(flag_C)
ACCESSOR_TESTS(flag_I)
ACCESSOR_TESTS(flag_D)
ACCESSOR_TESTS(flag_V)

} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
