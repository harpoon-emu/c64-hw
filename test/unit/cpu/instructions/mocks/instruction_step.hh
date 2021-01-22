#ifndef TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_INSTRUCTION_STEP_HH
#define TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_INSTRUCTION_STEP_HH

#include "../src/cpu/instructions/instruction_step.hh"

#include <harpoon/c64-hw/cpu/mos_6510.hh>

#include <gmock/gmock.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {
namespace mocks {

template<typename CPU>
class instruction_step : public c64::hw::cpu::instructions::instruction_step<CPU> {
public:
	using c64::hw::cpu::instructions::instruction_step<CPU>::instruction_step;

	MOCK_METHOD(std::uint32_t, check, (), (override));
	MOCK_METHOD(void, execute, (), (override));
};

} // namespace mocks
} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test


#endif