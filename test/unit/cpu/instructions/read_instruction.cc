#include "../src/cpu/instructions/read_instruction.hh"

#include "../src/cpu/instructions/data_accessor.hh"
#include "instruction_step.hh"
#include "instructions_test.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

template<typename T, typename REG, bool UPDATE_FLAGS, T V>
class load_register
    : public instruction_step_test<c64::hw::cpu::instructions::load_register<
          mocks::mos_6510, T, REG,
          c64::hw::cpu::instructions::value_accessor<mocks::mos_6510, T, V>, UPDATE_FLAGS>> {};

#define LOAD_REGISTER_TEST__(T, REG, UPDATE_FLAGS, V)                                          \
	class load_register_##REG##_##UPDATE_FLAGS##_##V                                           \
	    : public load_register<T, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>, \
	                           UPDATE_FLAGS, V> {};                                            \
                                                                                               \
	TEST_F(load_register_##REG##_##UPDATE_FLAGS##_##V, check) {                                \
		test_check();                                                                          \
	}                                                                                          \
                                                                                               \
	TEST_F(load_register_##REG##_##UPDATE_FLAGS##_##V, step) {                                 \
		EXPECT_CALL(_mos_6510, set_##REG(V)).Times(1);                                         \
		_set_flags_expectations<T>(UPDATE_FLAGS, V);                                           \
		test_step();                                                                           \
	}

#define LOAD_REGISTER_TEST_(T, REG, V)     \
	LOAD_REGISTER_TEST__(T, REG, true, V); \
	LOAD_REGISTER_TEST__(T, REG, false, V);

#define LOAD_REGISTER_TEST_U8(REG)                \
	LOAD_REGISTER_TEST_(std::uint8_t, REG, 0x00); \
	LOAD_REGISTER_TEST_(std::uint8_t, REG, 0x01); \
	LOAD_REGISTER_TEST_(std::uint8_t, REG, 0x7F); \
	LOAD_REGISTER_TEST_(std::uint8_t, REG, 0x80); \
	LOAD_REGISTER_TEST_(std::uint8_t, REG, 0x8F); \
	LOAD_REGISTER_TEST_(std::uint8_t, REG, 0xFF);

#define LOAD_REGISTER_TEST_U16(REG)                  \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x0000); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x0001); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x007F); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x0080); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x008F); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x00FF); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x0100); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x0101); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x017F); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x0180); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x108F); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x8000); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x80FF); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x7FFF); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0x8FFF); \
	LOAD_REGISTER_TEST_(std::uint16_t, REG, 0xFFFF);


LOAD_REGISTER_TEST_U8(A);
LOAD_REGISTER_TEST_U8(X);
LOAD_REGISTER_TEST_U8(Y);
LOAD_REGISTER_TEST_U8(latch);
LOAD_REGISTER_TEST_U8(PCL);
LOAD_REGISTER_TEST_U8(PCH);
LOAD_REGISTER_TEST_U8(P);
LOAD_REGISTER_TEST_U16(PC);


template<typename REG, std::uint8_t V>
class compare_register
    : public instruction_step_test<c64::hw::cpu::instructions::compare_register<
          mocks::mos_6510, REG,
          c64::hw::cpu::instructions::value_accessor<mocks::mos_6510, std::uint8_t, V>>> {};

#define COMPARE_REGISTER_TEST_(REG, V)                                                             \
	class compare_register_##REG##_##V                                                             \
	    : public compare_register<c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>, V>, \
	      public ::testing::WithParamInterface<std::uint16_t> {};                                  \
                                                                                                   \
	TEST_P(compare_register_##REG##_##V, check) {                                                  \
		test_check();                                                                              \
	}                                                                                              \
                                                                                                   \
	TEST_P(compare_register_##REG##_##V, step) {                                                   \
		std::uint8_t R = GetParam() & 0xFF;                                                        \
		EXPECT_CALL(_mos_6510, get_##REG).Times(1).WillOnce(::testing::Return(R));                 \
		EXPECT_CALL(_mos_6510, set_flag_N(((R - V) & 0x80) == 0x80)).Times(1);                     \
		EXPECT_CALL(_mos_6510, set_flag_Z(R == V)).Times(1);                                       \
		EXPECT_CALL(_mos_6510, set_flag_C(R >= V)).Times(1);                                       \
		EXPECT_CALL(_mos_6510, set_flag_I).Times(0);                                               \
		EXPECT_CALL(_mos_6510, set_flag_D).Times(0);                                               \
		EXPECT_CALL(_mos_6510, set_flag_V).Times(0);                                               \
		EXPECT_CALL(_mos_6510, set_P).Times(0);                                                    \
		test_step();                                                                               \
	}                                                                                              \
                                                                                                   \
	INSTANTIATE_TEST_SUITE_P(Full, compare_register_##REG##_##V,                                   \
	                         ::testing::Values(0x00, 0x01, 0x0E, 0x0F, 0x10, 0x3F, 0x40, 0x41,     \
	                                           0x7F, 0x80, 0x8F, 0xF0, 0xFF));

#define COMPARE_REGISTER_TEST(REG)     \
	COMPARE_REGISTER_TEST_(REG, 0x00); \
	COMPARE_REGISTER_TEST_(REG, 0x01); \
	COMPARE_REGISTER_TEST_(REG, 0x0E); \
	COMPARE_REGISTER_TEST_(REG, 0x0F); \
	COMPARE_REGISTER_TEST_(REG, 0x10); \
	COMPARE_REGISTER_TEST_(REG, 0x3F); \
	COMPARE_REGISTER_TEST_(REG, 0x40); \
	COMPARE_REGISTER_TEST_(REG, 0x41); \
	COMPARE_REGISTER_TEST_(REG, 0x7F); \
	COMPARE_REGISTER_TEST_(REG, 0x80); \
	COMPARE_REGISTER_TEST_(REG, 0x8F); \
	COMPARE_REGISTER_TEST_(REG, 0xF0); \
	COMPARE_REGISTER_TEST_(REG, 0xFF);

COMPARE_REGISTER_TEST(A);
COMPARE_REGISTER_TEST(X);
COMPARE_REGISTER_TEST(Y);


} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
