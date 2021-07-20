#ifndef TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_MEMORY_HH
#define TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_MEMORY_HH

#include <harpoon/c64-hw/memory/memory.hh>

#include <gmock/gmock.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {
namespace mocks {

class memory : public c64::hw::memory::memory {
public:
	MOCK_METHOD(void, create, (), ());

	MOCK_METHOD(void, get_cell, (harpoon::memory::address address, std::uint8_t &value), ());
	MOCK_METHOD(void, set_cell, (harpoon::memory::address address, std::uint8_t value), ());

	MOCK_METHOD(void, switch_d000_dfff, (harpoon::memory::multiplexed_memory::memory_id mem_id),
	            ());
};

} // namespace mocks
} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test


#endif