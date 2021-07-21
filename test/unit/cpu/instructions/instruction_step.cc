#include "../src/cpu/instructions/instruction_step.hh"

#include "instructions_test.hh"

#include <harpoon/c64-hw/cpu/mos_6510.hh>
#include <harpoon/execution/instruction.hh>

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

class instruction_step : public instruction_step_test<mocks::instruction_step<mocks::mos_6510>> {};

TEST_F(instruction_step, set_delay) {
	_instruction_step_ut.set_delay(0);
	EXPECT_EQ(_instruction_step_ut.get_delay(), 0);

	_instruction_step_ut.set_delay(255);
	EXPECT_EQ(_instruction_step_ut.get_delay(), 255);

	_instruction_step_ut.set_delay(1024);
	EXPECT_EQ(_instruction_step_ut.get_delay(), 1024);
}

TEST_F(instruction_step, add_delay) {
	_instruction_step_ut.set_delay(0);
	EXPECT_EQ(_instruction_step_ut.get_delay(), 0);

	_instruction_step_ut.add_delay(255);
	EXPECT_EQ(_instruction_step_ut.get_delay(), 255);

	_instruction_step_ut.add_delay(1024);
	EXPECT_EQ(_instruction_step_ut.get_delay(), 255 + 1024);
}

TEST_F(instruction_step, step) {
	EXPECT_CALL(_instruction_step_ut, execute).Times(1);
	test_step();
}

class internal_read
    : public instruction_step_test<c64::hw::cpu::instructions::internal_read<mocks::mos_6510>> {};

TEST_F(internal_read, check) {
	test_check();
}

TEST_F(internal_read, step) {
	test_step();
}

class internal_write
    : public instruction_step_test<c64::hw::cpu::instructions::internal_write<mocks::mos_6510>> {};

TEST_F(internal_write, check) {
	test_check();
}

TEST_F(internal_write, step) {
	test_step();
}

class fetch_program_code : public instruction_step_test<
                               c64::hw::cpu::instructions::fetch_program_code<mocks::mos_6510>> {};

TEST_F(fetch_program_code, check) {
	test_check();
}

TEST_F(fetch_program_code, step) {
	EXPECT_CALL(_mos_6510, internal_read_program_code).Times(1);
	_set_flags_expectations(false, 0);
	test_step();
}

template<bool X_INDEX>
class fetch_indirect_pointer
    : public instruction_step_test<
          c64::hw::cpu::instructions::fetch_indirect_pointer<mocks::mos_6510, X_INDEX>> {};

#define FETCH_INDIRECT_POINTER_TEST(X_INDEX)                                            \
	class fetch_indirect_pointer_##X_INDEX : public fetch_indirect_pointer<X_INDEX> {}; \
                                                                                        \
	TEST_F(fetch_indirect_pointer_##X_INDEX, check) {                                   \
		test_check();                                                                   \
	}                                                                                   \
                                                                                        \
	TEST_F(fetch_indirect_pointer_##X_INDEX, step) {                                    \
		EXPECT_CALL(_mos_6510, fetch_indirect_pointer(X_INDEX)).Times(1);               \
		_set_flags_expectations(false, 0);                                              \
		test_step();                                                                    \
	}

FETCH_INDIRECT_POINTER_TEST(true);
FETCH_INDIRECT_POINTER_TEST(false);

template<typename REG, bool UPDATE_NZ>
class stack_pull : public instruction_step_test<
                       c64::hw::cpu::instructions::stack_pull<mocks::mos_6510, REG, UPDATE_NZ>> {};

#define STACK_PULL_TEST(REG, UPDATE_NZ)                                                          \
	class stack_pull_##REG##_##UPDATE_NZ                                                         \
	    : public stack_pull<c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>,         \
	                        UPDATE_NZ>,                                                          \
	      public ::testing::WithParamInterface<std::uint16_t> {};                                \
                                                                                                 \
	TEST_P(stack_pull_##REG##_##UPDATE_NZ, check) {                                              \
		test_check();                                                                            \
	}                                                                                            \
                                                                                                 \
	TEST_P(stack_pull_##REG##_##UPDATE_NZ, step) {                                               \
		std::uint8_t v = GetParam() & 0xFF;                                                      \
		EXPECT_CALL(_mos_6510, stack_pull).Times(1).WillOnce([v](std::uint8_t &dt) { dt = v; }); \
		EXPECT_CALL(_mos_6510, set_##REG(v)).Times(1);                                           \
		_set_flags_expectations(UPDATE_NZ, v);                                                   \
		test_step();                                                                             \
	}                                                                                            \
                                                                                                 \
	INSTANTIATE_TEST_SUITE_P(Full, stack_pull_##REG##_##UPDATE_NZ,                               \
	                         ::testing::Range<std::uint16_t>(0, 256));


STACK_PULL_TEST(A, true);
STACK_PULL_TEST(A, false);
STACK_PULL_TEST(X, true);
STACK_PULL_TEST(X, false);
STACK_PULL_TEST(Y, true);
STACK_PULL_TEST(Y, false);
STACK_PULL_TEST(P, true);
STACK_PULL_TEST(P, false);
STACK_PULL_TEST(PCL, true);
STACK_PULL_TEST(PCL, false);
STACK_PULL_TEST(PCH, true);
STACK_PULL_TEST(PCH, false);

template<typename REG>
class stack_push
    : public instruction_step_test<c64::hw::cpu::instructions::stack_push<mocks::mos_6510, REG>> {};

#define STACK_PUSH_TEST(REG)                                                              \
	class stack_push_##REG                                                                \
	    : public stack_push<c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>, \
	      public ::testing::WithParamInterface<std::uint16_t> {};                         \
                                                                                          \
	TEST_P(stack_push_##REG, check) {                                                     \
		test_check();                                                                     \
	}                                                                                     \
                                                                                          \
	TEST_P(stack_push_##REG, step) {                                                      \
		std::uint8_t v = GetParam() & 0xFF;                                               \
		EXPECT_CALL(_mos_6510, get_##REG).Times(1).WillOnce(::testing::Return(v));        \
		EXPECT_CALL(_mos_6510, stack_push(v)).Times(1);                                   \
		_set_flags_expectations(false, v);                                                \
		test_step();                                                                      \
	}                                                                                     \
                                                                                          \
	INSTANTIATE_TEST_SUITE_P(Full, stack_push_##REG, ::testing::Range<std::uint16_t>(0, 256));


STACK_PUSH_TEST(A);
STACK_PUSH_TEST(X);
STACK_PUSH_TEST(Y);
STACK_PUSH_TEST(P);
STACK_PUSH_TEST(PCL);
STACK_PUSH_TEST(PCH);

template<typename FLAG, bool VALUE>
class set_flag : public instruction_step_test<
                     c64::hw::cpu::instructions::set_flag<mocks::mos_6510, FLAG, VALUE>> {};

#define SET_FLAG_TEST(FLAG, VALUE)                                                             \
	class set_flag_##FLAG##_##VALUE                                                            \
	    : public set_flag<c64::hw::cpu::instructions::flag_##FLAG##_accessor<mocks::mos_6510>, \
	                      VALUE> {};                                                           \
                                                                                               \
	TEST_F(set_flag_##FLAG##_##VALUE, check) {                                                 \
		test_check();                                                                          \
	}                                                                                          \
                                                                                               \
	TEST_F(set_flag_##FLAG##_##VALUE, step) {                                                  \
		EXPECT_CALL(_mos_6510, set_flag_N(::testing::_)).Times(0);                             \
		EXPECT_CALL(_mos_6510, set_flag_Z(::testing::_)).Times(0);                             \
		EXPECT_CALL(_mos_6510, set_flag_C(::testing::_)).Times(0);                             \
		EXPECT_CALL(_mos_6510, set_flag_I(::testing::_)).Times(0);                             \
		EXPECT_CALL(_mos_6510, set_flag_D(::testing::_)).Times(0);                             \
		EXPECT_CALL(_mos_6510, set_flag_V(::testing::_)).Times(0);                             \
		EXPECT_CALL(_mos_6510, set_flag_##FLAG(VALUE)).Times(1);                               \
		test_step();                                                                           \
	}

SET_FLAG_TEST(N, true);
SET_FLAG_TEST(N, false);
SET_FLAG_TEST(Z, true);
SET_FLAG_TEST(Z, false);
SET_FLAG_TEST(C, true);
SET_FLAG_TEST(C, false);
SET_FLAG_TEST(I, true);
SET_FLAG_TEST(I, false);
SET_FLAG_TEST(D, true);
SET_FLAG_TEST(D, false);
SET_FLAG_TEST(V, true);
SET_FLAG_TEST(V, false);

} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
