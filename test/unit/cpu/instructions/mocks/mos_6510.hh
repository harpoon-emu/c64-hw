#ifndef TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_MOS_6510_HH
#define TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_MOS_6510_HH

#include <harpoon/c64-hw/cpu/mos_6510.hh>

#include <gmock/gmock.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {
namespace mocks {

class mos_6510 : public c64::hw::cpu::mos_6510 {
public:
	MOCK_METHOD(void, set_P, (std::uint8_t), ());
	MOCK_METHOD(void, set_flag_N, (bool), ());
	MOCK_METHOD(void, set_flag_Z, (bool), ());
	MOCK_METHOD(void, set_flag_C, (bool), ());
	MOCK_METHOD(void, set_flag_I, (bool), ());
	MOCK_METHOD(void, set_flag_D, (bool), ());
	MOCK_METHOD(void, set_flag_V, (bool), ());

	MOCK_METHOD(std::uint8_t, get_P, (), (const));
	MOCK_METHOD(bool, get_flag_N, (), (const));
	MOCK_METHOD(bool, get_flag_Z, (), (const));
	MOCK_METHOD(bool, get_flag_C, (), (const));
	MOCK_METHOD(bool, get_flag_I, (), (const));
	MOCK_METHOD(bool, get_flag_D, (), (const));
	MOCK_METHOD(bool, get_flag_V, (), (const));

	MOCK_METHOD(void, set_A, (std::uint8_t), ());
	MOCK_METHOD(void, set_X, (std::uint8_t), ());
	MOCK_METHOD(void, set_Y, (std::uint8_t), ());
	MOCK_METHOD(void, set_SP, (std::uint8_t), ());
	MOCK_METHOD(void, set_PC, (std::uint16_t), ());
	MOCK_METHOD(void, set_PCL, (std::uint8_t), ());
	MOCK_METHOD(void, set_PCH, (std::uint8_t), ());
	MOCK_METHOD(void, set_latch, (std::uint8_t), ());

	MOCK_METHOD(std::uint8_t, get_A, (), (const));
	MOCK_METHOD(std::uint8_t, get_X, (), (const));
	MOCK_METHOD(std::uint8_t, get_Y, (), (const));
	MOCK_METHOD(std::uint8_t, get_SP, (), (const));
	MOCK_METHOD(std::uint16_t, get_PC, (), (const));
	MOCK_METHOD(std::uint8_t, get_PCL, (), (const));
	MOCK_METHOD(std::uint8_t, get_PCH, (), (const));
	MOCK_METHOD(std::uint8_t, get_latch, (), (const));
};

} // namespace mocks
} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test


#endif