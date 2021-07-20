#include "../src/cpu/instructions/data_accessor.hh"

#include "instructions_test.hh"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

static auto u8_values = ::testing::Values<std::uint8_t>(0x00, 0x01, 0x02, 0x40, 0x78, 0x79, 0x80,
                                                        0x81, 0xC0, 0xF0, 0xFE, 0xFF);

static auto u16_values = ::testing::Values<std::uint16_t>(0x0000, 0x0001, 0x0002, 0x007F, 0x0080,
                                                          0x0081, 0x00FE, 0x00FF, 0x00100, 0x7FFF,
                                                          0x8000, 0x8001, 0xC000, 0xFFFE, 0xFFFF);

template<typename T>
std::string param_test_print_tuple_2(const testing::TestParamInfo<typename T::ParamType> &info) {
	std::string name = std::get<0>(info.param) ? "T" : "F";
	name += "_";
	name += std::to_string(std::get<1>(info.param));
	return name;
}

template<typename T>
std::string param_test_print_tuple_3(const testing::TestParamInfo<typename T::ParamType> &info) {
	std::string name;
	name += std::to_string(std::get<0>(info.param));
	name += "_";
	name += std::to_string(std::get<1>(info.param));
	name += "_";
	name += std::to_string(std::get<2>(info.param));
	return name;
}

template<typename T>
std::string param_test_print_tuple_4(const testing::TestParamInfo<typename T::ParamType> &info) {
	std::string name = std::get<0>(info.param) ? "T" : "F";
	name += "_";
	name += std::to_string(std::get<1>(info.param));
	name += "_";
	name += std::to_string(std::get<2>(info.param));
	name += "_";
	name += std::to_string(std::get<3>(info.param));
	return name;
}

template<typename T>
class data_accessor : public instructions_test {
protected:
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
};

#define REGISTER_ACCESSOR_TEST(REG)                                                       \
	class register_accessor_##REG                                                         \
	    : public data_accessor<std::uint8_t>,                                             \
	      public ::testing::WithParamInterface<std::tuple<bool, std::uint16_t>> {};       \
                                                                                          \
	TEST_P(register_accessor_##REG, fetch) {                                              \
		c64::hw::cpu::instructions::register_accessor<                                    \
		    mocks::mos_6510, std::uint8_t,                                                \
		    c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>                  \
		    d(&_mos_6510, &_instruction_step);                                            \
		auto p = GetParam();                                                              \
		std::uint8_t v = std::get<1>(p) & 0xFF;                                           \
                                                                                          \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(v));               \
		_set_flags_expectations(std::get<0>(p), v);                                       \
		EXPECT_EQ(d.fetch(std::get<0>(p)), v);                                            \
	}                                                                                     \
                                                                                          \
	INSTANTIATE_TEST_SUITE_P(Full, register_accessor_##REG,                               \
	                         ::testing::Combine(::testing::Values(true, false),           \
	                                            ::testing::Range<std::uint16_t>(0, 256)), \
	                         param_test_print_tuple_2<register_accessor_##REG>);

REGISTER_ACCESSOR_TEST(A);
REGISTER_ACCESSOR_TEST(X);
REGISTER_ACCESSOR_TEST(Y);
REGISTER_ACCESSOR_TEST(SP);
REGISTER_ACCESSOR_TEST(latch);

class value_accessor : public data_accessor<std::uint8_t>,
                       public ::testing::WithParamInterface<bool> {};

#define VALUE_ACCESSOR_TEST(v)                                                          \
	TEST_P(value_accessor, fetch_##v) {                                                 \
		bool f = GetParam();                                                            \
                                                                                        \
		c64::hw::cpu::instructions::value_accessor<mocks::mos_6510, std::uint8_t, v> d( \
		    &_mos_6510, &_instruction_step);                                            \
		_set_flags_expectations(f, v);                                                  \
		EXPECT_EQ(d.fetch(f), v);                                                       \
	}

VALUE_ACCESSOR_TEST(0x00);
VALUE_ACCESSOR_TEST(0x01);
VALUE_ACCESSOR_TEST(0x02);
VALUE_ACCESSOR_TEST(0x40);
VALUE_ACCESSOR_TEST(0x78);
VALUE_ACCESSOR_TEST(0x79);
VALUE_ACCESSOR_TEST(0x80);
VALUE_ACCESSOR_TEST(0x81);
VALUE_ACCESSOR_TEST(0xC0);
VALUE_ACCESSOR_TEST(0xF0);
VALUE_ACCESSOR_TEST(0xFE);
VALUE_ACCESSOR_TEST(0xFF);

INSTANTIATE_TEST_SUITE_P(Full, value_accessor, ::testing::Values(true, false));

class program_code_accessor
    : public data_accessor<std::uint16_t>,
      public ::testing::WithParamInterface<std::tuple<bool, std::uint16_t>> {};

TEST_P(program_code_accessor, fetch) {
	c64::hw::cpu::instructions::program_code_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                     &_instruction_step);
	auto p = GetParam();
	std::uint16_t v = std::get<1>(p);

	{
		::testing::InSequence seq;
		EXPECT_CALL(_mos_6510, internal_read_program_code).Times(1);
		EXPECT_CALL(_mos_6510, get_internal_memory_access)
		    .Times(1)
		    .WillOnce(::testing::Return<c64::hw::cpu::mos_6510::internal_memory_access>({v}));
	}
	_set_flags_expectations(std::get<0>(p), v);
	EXPECT_EQ(d.fetch(std::get<0>(p)), v);
}

INSTANTIATE_TEST_SUITE_P(Full, program_code_accessor,
                         ::testing::Combine(::testing::Values(true, false), u16_values),
                         param_test_print_tuple_2<program_code_accessor>);


class immediate_accessor : public data_accessor<std::uint8_t>,
                           public ::testing::WithParamInterface<std::tuple<bool, std::uint16_t>> {};

TEST_P(immediate_accessor, fetch) {
	c64::hw::cpu::instructions::immediate_accessor<mocks::mos_6510, std::uint8_t> d(
	    &_mos_6510, &_instruction_step);
	auto p = GetParam();
	std::uint8_t v = std::get<1>(p) & 0xFF;

	EXPECT_CALL(_mos_6510, get_program_code(::testing::_)).Times(1).WillOnce([v](std::uint8_t &dt) {
		dt = v;
	});
	_set_flags_expectations(std::get<0>(p), v);
	EXPECT_EQ(d.fetch(std::get<0>(p)), v);
}

INSTANTIATE_TEST_SUITE_P(Full, immediate_accessor,
                         ::testing::Combine(::testing::Values(true, false),
                                            ::testing::Range<std::uint16_t>(0, 256)),
                         param_test_print_tuple_2<immediate_accessor>);

class memory_accessor : public data_accessor<std::uint8_t>,
                        public ::testing::WithParamInterface<
                            std::tuple<bool, std::uint16_t, std::uint8_t, std::uint8_t>> {};

TEST_P(memory_accessor, fetch) {
	c64::hw::cpu::instructions::memory_accessor<mocks::mos_6510> d(&_mos_6510, &_instruction_step);
	auto p = GetParam();
	std::uint16_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFFFF, ::testing::_))
	    .Times(1)
	    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });
	_set_flags_expectations(std::get<0>(p), v);
	_instruction_step.set_delay(start);
	EXPECT_EQ(d.fetch(a, i, std::get<0>(p)), v);
	EXPECT_EQ(_instruction_step.get_delay(), start + ((a & 0xFF00) == ((a + i) & 0xFF00) ? 0 : 1));
}

TEST_P(memory_accessor, store) {
	c64::hw::cpu::instructions::memory_accessor<mocks::mos_6510> d(&_mos_6510, &_instruction_step);
	auto p = GetParam();
	std::uint16_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFFFF, v)).Times(1);
	_set_flags_expectations(false, v);
	_instruction_step.set_delay(start);
	d.store(v, a, i);
	EXPECT_EQ(_instruction_step.get_delay(), start);
}

INSTANTIATE_TEST_SUITE_P(Address, memory_accessor,
                         ::testing::Combine(::testing::Values(true, false), u16_values, u8_values,
                                            u8_values),
                         param_test_print_tuple_4<memory_accessor>);


class zero_page_accessor : public data_accessor<std::uint8_t>,
                           public ::testing::WithParamInterface<
                               std::tuple<bool, std::uint8_t, std::uint8_t, std::uint8_t>> {};

TEST_P(zero_page_accessor, fetch) {
	c64::hw::cpu::instructions::zero_page_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                  &_instruction_step);
	auto p = GetParam();
	std::uint8_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {
		union c64::hw::cpu::mos_6510::internal_memory_access ma;
		ma.b.current = a;
		ma.b.previous = 0x00;
		return ma;
	});
	EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFF, ::testing::_))
	    .Times(1)
	    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });
	_set_flags_expectations(std::get<0>(p), v);
	_instruction_step.set_delay(start);
	EXPECT_EQ(d.fetch(std::get<0>(p), i), v);
	EXPECT_EQ(_instruction_step.get_delay(), start);
}

TEST_P(zero_page_accessor, store) {
	c64::hw::cpu::instructions::zero_page_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                  &_instruction_step);
	auto p = GetParam();
	std::uint8_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {
		union c64::hw::cpu::mos_6510::internal_memory_access ma;
		ma.b.current = a;
		ma.b.previous = 0x00;
		return ma;
	});
	EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFF, v)).Times(1);
	_set_flags_expectations(false, v);
	_instruction_step.set_delay(start);
	d.store(v, i);
	EXPECT_EQ(_instruction_step.get_delay(), start);
}

INSTANTIATE_TEST_SUITE_P(Address, zero_page_accessor,
                         ::testing::Combine(::testing::Values(true, false), u8_values, u8_values,
                                            u8_values),
                         param_test_print_tuple_4<zero_page_accessor>);

#define INDEXED_ZERO_PAGE_ACCESSOR_TEST(REG)                                                 \
	class indexed_zero_page_accessor_##REG                                                   \
	    : public data_accessor<std::uint8_t>,                                                \
	      public ::testing::WithParamInterface<                                              \
	          std::tuple<bool, std::uint8_t, std::uint8_t, std::uint8_t>> {};                \
                                                                                             \
	TEST_P(indexed_zero_page_accessor_##REG, fetch) {                                        \
		c64::hw::cpu::instructions::indexed_zero_page_accessor<                              \
		    mocks::mos_6510, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>    \
		    d(&_mos_6510, &_instruction_step);                                               \
		auto p = GetParam();                                                                 \
		std::uint8_t a = std::get<1>(p) & 0xFF;                                              \
		std::uint16_t i = std::get<2>(p);                                                    \
		std::uint8_t v = std::get<3>(p) & 0xFF;                                              \
		std::uint32_t start = std::rand() & 0x7FFFFFF;                                       \
                                                                                             \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(i));                  \
		EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {       \
			union c64::hw::cpu::mos_6510::internal_memory_access ma;                         \
			ma.b.current = a;                                                                \
			ma.b.previous = 0x00;                                                            \
			return ma;                                                                       \
		});                                                                                  \
		EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFF, ::testing::_))                  \
		    .Times(1)                                                                        \
		    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });                     \
		_set_flags_expectations(std::get<0>(p), v);                                          \
		_instruction_step.set_delay(start);                                                  \
		EXPECT_EQ(d.fetch(std::get<0>(p)), v);                                               \
		EXPECT_EQ(_instruction_step.get_delay(), start);                                     \
	}                                                                                        \
                                                                                             \
	TEST_P(indexed_zero_page_accessor_##REG, store) {                                        \
		c64::hw::cpu::instructions::indexed_zero_page_accessor<                              \
		    mocks::mos_6510, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>    \
		    d(&_mos_6510, &_instruction_step);                                               \
		auto p = GetParam();                                                                 \
		std::uint8_t a = std::get<1>(p) & 0xFF;                                              \
		std::uint16_t i = std::get<2>(p);                                                    \
		std::uint8_t v = std::get<3>(p) & 0xFF;                                              \
		std::uint32_t start = std::rand() & 0x7FFFFFF;                                       \
                                                                                             \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(i));                  \
		EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {       \
			union c64::hw::cpu::mos_6510::internal_memory_access ma;                         \
			ma.b.current = a;                                                                \
			ma.b.previous = 0x00;                                                            \
			return ma;                                                                       \
		});                                                                                  \
		EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFF, v)).Times(1);                   \
		_set_flags_expectations(false, v);                                                   \
		_instruction_step.set_delay(start);                                                  \
		d.store(v);                                                                          \
		EXPECT_EQ(_instruction_step.get_delay(), start);                                     \
	}                                                                                        \
                                                                                             \
	INSTANTIATE_TEST_SUITE_P(                                                                \
	    Full, indexed_zero_page_accessor_##REG,                                              \
	    ::testing::Combine(::testing::Values(true, false), u8_values, u8_values, u8_values), \
	    param_test_print_tuple_4<indexed_zero_page_accessor_##REG>);

INDEXED_ZERO_PAGE_ACCESSOR_TEST(X);
INDEXED_ZERO_PAGE_ACCESSOR_TEST(Y);

class absolute_accessor : public data_accessor<std::uint8_t>,
                          public ::testing::WithParamInterface<
                              std::tuple<bool, std::uint16_t, std::uint8_t, std::uint8_t>> {};

TEST_P(absolute_accessor, fetch) {
	c64::hw::cpu::instructions::absolute_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                 &_instruction_step);
	auto p = GetParam();
	std::uint16_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {
		union c64::hw::cpu::mos_6510::internal_memory_access ma;
		ma.w = a;
		return ma;
	});
	EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFFFF, ::testing::_))
	    .Times(1)
	    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });
	_set_flags_expectations(std::get<0>(p), v);
	_instruction_step.set_delay(start);
	EXPECT_EQ(d.fetch(std::get<0>(p), i), v);
	EXPECT_EQ(_instruction_step.get_delay(), start + ((a & 0xFF00) == ((a + i) & 0xFF00) ? 0 : 1));
}

TEST_P(absolute_accessor, store) {
	c64::hw::cpu::instructions::absolute_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                 &_instruction_step);
	auto p = GetParam();
	std::uint16_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {
		union c64::hw::cpu::mos_6510::internal_memory_access ma;
		ma.w = a;
		return ma;
	});
	EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFFFF, v)).Times(1);
	_set_flags_expectations(false, v);
	_instruction_step.set_delay(start);
	d.store(v, i);
	EXPECT_EQ(_instruction_step.get_delay(), start);
}

INSTANTIATE_TEST_SUITE_P(Address, absolute_accessor,
                         ::testing::Combine(::testing::Values(true, false), u16_values, u8_values,
                                            u8_values),
                         param_test_print_tuple_4<absolute_accessor>);


#define INDEXED_ABSOLUTE_ACCESSOR_TEST(REG)                                                   \
	class indexed_absolute_accessor_##REG                                                     \
	    : public data_accessor<std::uint8_t>,                                                 \
	      public ::testing::WithParamInterface<                                               \
	          std::tuple<bool, std::uint16_t, std::uint8_t, std::uint8_t>> {};                \
                                                                                              \
	TEST_P(indexed_absolute_accessor_##REG, fetch) {                                          \
		c64::hw::cpu::instructions::indexed_absolute_accessor<                                \
		    mocks::mos_6510, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>     \
		    d(&_mos_6510, &_instruction_step);                                                \
		auto p = GetParam();                                                                  \
		std::uint16_t a = std::get<1>(p);                                                     \
		std::uint8_t i = std::get<2>(p);                                                      \
		std::uint8_t v = std::get<3>(p);                                                      \
		std::uint32_t start = std::rand() & 0x7FFFFFF;                                        \
                                                                                              \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(i));                   \
		EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {        \
			union c64::hw::cpu::mos_6510::internal_memory_access ma;                          \
			ma.w = a;                                                                         \
			return ma;                                                                        \
		});                                                                                   \
		EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFFFF, ::testing::_))                 \
		    .Times(1)                                                                         \
		    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });                      \
		_set_flags_expectations(std::get<0>(p), v);                                           \
		_instruction_step.set_delay(start);                                                   \
		EXPECT_EQ(d.fetch(std::get<0>(p)), v);                                                \
		EXPECT_EQ(_instruction_step.get_delay(),                                              \
		          start + ((a & 0xFF00) == ((a + i) & 0xFF00) ? 0 : 1));                      \
	}                                                                                         \
                                                                                              \
	TEST_P(indexed_absolute_accessor_##REG, store) {                                          \
		c64::hw::cpu::instructions::indexed_absolute_accessor<                                \
		    mocks::mos_6510, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>     \
		    d(&_mos_6510, &_instruction_step);                                                \
		auto p = GetParam();                                                                  \
		std::uint16_t a = std::get<1>(p);                                                     \
		std::uint8_t i = std::get<2>(p);                                                      \
		std::uint8_t v = std::get<3>(p);                                                      \
		std::uint32_t start = std::rand() & 0x7FFFFFF;                                        \
                                                                                              \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(i));                   \
		EXPECT_CALL(_mos_6510, get_internal_memory_access()).Times(1).WillOnce([a]() {        \
			union c64::hw::cpu::mos_6510::internal_memory_access ma;                          \
			ma.w = a;                                                                         \
			return ma;                                                                        \
		});                                                                                   \
		EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFFFF, v)).Times(1);                  \
		_set_flags_expectations(false, v);                                                    \
		_instruction_step.set_delay(start);                                                   \
		d.store(v);                                                                           \
		EXPECT_EQ(_instruction_step.get_delay(), start);                                      \
	}                                                                                         \
                                                                                              \
	INSTANTIATE_TEST_SUITE_P(                                                                 \
	    Full, indexed_absolute_accessor_##REG,                                                \
	    ::testing::Combine(::testing::Values(true, false), u16_values, u8_values, u8_values), \
	    param_test_print_tuple_4<indexed_absolute_accessor_##REG>);

INDEXED_ABSOLUTE_ACCESSOR_TEST(X);
INDEXED_ABSOLUTE_ACCESSOR_TEST(Y);


class indirect_accessor : public data_accessor<std::uint8_t>,
                          public ::testing::WithParamInterface<
                              std::tuple<bool, std::uint16_t, std::uint8_t, std::uint8_t>> {};

TEST_P(indirect_accessor, fetch) {
	c64::hw::cpu::instructions::indirect_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                 &_instruction_step);
	auto p = GetParam();
	std::uint16_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(_mos_6510, get_indirect_pointer()).Times(1).WillOnce(::testing::Return(a));
	EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFFFF, ::testing::_))
	    .Times(1)
	    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });
	_set_flags_expectations(std::get<0>(p), v);
	_instruction_step.set_delay(start);
	EXPECT_EQ(d.fetch(std::get<0>(p), i), v);
	EXPECT_EQ(_instruction_step.get_delay(), start + ((a & 0xFF00) == ((a + i) & 0xFF00) ? 0 : 1));
}

TEST_P(indirect_accessor, store) {
	c64::hw::cpu::instructions::indirect_accessor<mocks::mos_6510> d(&_mos_6510,
	                                                                 &_instruction_step);
	auto p = GetParam();
	std::uint16_t a = std::get<1>(p);
	std::uint8_t i = std::get<2>(p);
	std::uint8_t v = std::get<3>(p);
	std::uint32_t start = std::rand() & 0x7FFFFFF;

	EXPECT_CALL(_mos_6510, get_indirect_pointer()).Times(1).WillOnce(::testing::Return(a));
	EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFFFF, v)).Times(1);
	_set_flags_expectations(false, v);
	_instruction_step.set_delay(start);
	d.store(v, i);
	EXPECT_EQ(_instruction_step.get_delay(), start);
}

INSTANTIATE_TEST_SUITE_P(Address, indirect_accessor,
                         ::testing::Combine(::testing::Values(true, false), u16_values, u8_values,
                                            u8_values),
                         param_test_print_tuple_4<indirect_accessor>);


#define INDEXED_INDIRECT_ACCESSOR_TEST(REG)                                                     \
	class indexed_indirect_accessor_##REG                                                       \
	    : public data_accessor<std::uint8_t>,                                                   \
	      public ::testing::WithParamInterface<                                                 \
	          std::tuple<bool, std::uint16_t, std::uint8_t, std::uint8_t>> {};                  \
                                                                                                \
	TEST_P(indexed_indirect_accessor_##REG, fetch) {                                            \
		c64::hw::cpu::instructions::indexed_indirect_accessor<                                  \
		    mocks::mos_6510, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>       \
		    d(&_mos_6510, &_instruction_step);                                                  \
		auto p = GetParam();                                                                    \
		std::uint16_t a = std::get<1>(p);                                                       \
		std::uint8_t i = std::get<2>(p);                                                        \
		std::uint8_t v = std::get<3>(p);                                                        \
		std::uint32_t start = std::rand() & 0x7FFFFFF;                                          \
                                                                                                \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(i));                     \
		EXPECT_CALL(_mos_6510, get_indirect_pointer()).Times(1).WillOnce(::testing::Return(a)); \
		EXPECT_CALL(*_memory.get(), get_cell((a + i) & 0xFFFF, ::testing::_))                   \
		    .Times(1)                                                                           \
		    .WillOnce([v](std::uint16_t, std::uint8_t &dt) { dt = v; });                        \
		_set_flags_expectations(std::get<0>(p), v);                                             \
		_instruction_step.set_delay(start);                                                     \
		EXPECT_EQ(d.fetch(std::get<0>(p)), v);                                                  \
		EXPECT_EQ(_instruction_step.get_delay(),                                                \
		          start + ((a & 0xFF00) == ((a + i) & 0xFF00) ? 0 : 1));                        \
	}                                                                                           \
                                                                                                \
	TEST_P(indexed_indirect_accessor_##REG, store) {                                            \
		c64::hw::cpu::instructions::indexed_indirect_accessor<                                  \
		    mocks::mos_6510, c64::hw::cpu::instructions::REG##_accessor<mocks::mos_6510>>       \
		    d(&_mos_6510, &_instruction_step);                                                  \
		auto p = GetParam();                                                                    \
		std::uint16_t a = std::get<1>(p);                                                       \
		std::uint8_t i = std::get<2>(p);                                                        \
		std::uint8_t v = std::get<3>(p);                                                        \
		std::uint32_t start = std::rand() & 0x7FFFFFF;                                          \
                                                                                                \
		EXPECT_CALL(_mos_6510, get_##REG()).WillOnce(::testing::Return(i));                     \
		EXPECT_CALL(_mos_6510, get_indirect_pointer()).Times(1).WillOnce(::testing::Return(a)); \
		EXPECT_CALL(*_memory.get(), set_cell((a + i) & 0xFFFF, v)).Times(1);                    \
		_set_flags_expectations(false, v);                                                      \
		_instruction_step.set_delay(start);                                                     \
		d.store(v);                                                                             \
		EXPECT_EQ(_instruction_step.get_delay(), start);                                        \
	}                                                                                           \
                                                                                                \
	INSTANTIATE_TEST_SUITE_P(                                                                   \
	    Full, indexed_indirect_accessor_##REG,                                                  \
	    ::testing::Combine(::testing::Values(true, false), u16_values, u8_values, u8_values),   \
	    param_test_print_tuple_4<indexed_indirect_accessor_##REG>);

INDEXED_INDIRECT_ACCESSOR_TEST(X);
INDEXED_INDIRECT_ACCESSOR_TEST(Y);


} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test