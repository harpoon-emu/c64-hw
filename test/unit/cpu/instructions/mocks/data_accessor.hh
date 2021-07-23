#ifndef TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_DATA_ACCESSOR_HH
#define TEST_UNIT_CPU_INSTRUCTIONS_MOCKS_DATA_ACCESSOR_HH

#include "../src/cpu/instructions/data_accessor.hh"

#include <gmock/gmock.h>

namespace test {
namespace unit {
namespace cpu {
namespace instructions {
namespace mocks {

template<typename CPU, typename T>
class test_data_accessor : public c64::hw::cpu::instructions::data_accessor<CPU, T> {
public:
	using c64::hw::cpu::instructions::data_accessor<CPU, T>::data_accessor;

	T fetch(bool update_flags) const {
		return c64::hw::cpu::instructions::data_accessor<CPU, std::uint8_t>::get_cpu()
		    ->test_fetch();
	}

	void store(T v) {
		return c64::hw::cpu::instructions::data_accessor<CPU, std::uint8_t>::get_cpu()->test_store(
		    v);
	}
};

} // namespace mocks
} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test


#endif