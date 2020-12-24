#ifndef CPU_INSTRUCTIONS_CPY_HH
#define CPU_INSTRUCTIONS_CPY_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cpy {

static constexpr const char *MNEMONIC = "CPY";

template<typename CPU, typename DATA>
using compare_y = compare_register<CPU, Y_accessor<CPU>, DATA>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xC0;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, compare_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xC4;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, compare_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xCC;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, compare_y>(cpu, MNEMONIC);
	}
};

} // namespace cpy
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
