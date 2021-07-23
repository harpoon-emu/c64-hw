#include "../src/cpu/instructions/write_instruction.hh"

#include "instruction_step.hh"
#include "instructions_test.hh"
#include "mocks/data_accessor.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

template<typename REG>
class store_register : public instruction_step_test<c64::hw::cpu::instructions::store_register<
                           mocks::mos_6510, std::uint8_t, REG,
                           mocks::test_data_accessor<mocks::mos_6510, std::uint8_t>>> {};

#define STORE_REGISTER_TEST(REG)                                                              \
	class store_register_##REG                                                                \
	    : public store_register<c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>, \
	      public ::testing::WithParamInterface<std::uint16_t> {};                             \
                                                                                              \
	TEST_P(store_register_##REG, check) {                                                     \
		test_check();                                                                         \
	}                                                                                         \
                                                                                              \
	TEST_P(store_register_##REG, step) {                                                      \
		std::uint8_t v = GetParam();                                                          \
		EXPECT_CALL(_mos_6510, get_##REG).Times(1).WillOnce(::testing::Return(v));            \
		EXPECT_CALL(_mos_6510, test_store(v)).Times(1);                                       \
		_set_flags_expectations<std::uint8_t>(false, v);                                      \
		test_step();                                                                          \
	}                                                                                         \
                                                                                              \
	INSTANTIATE_TEST_SUITE_P(Full, store_register_##REG, ::testing::Range<std::uint16_t>(0, 256));


STORE_REGISTER_TEST(A);
STORE_REGISTER_TEST(X);
STORE_REGISTER_TEST(Y);


} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
