#ifndef CPU_INSTRUCTIONS_CPX_HH
#define CPU_INSTRUCTIONS_CPX_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cpx {

static constexpr const char *MNEMONIC = "CPX";

template<typename CPU, typename DATA>
using compare_x = compare_register<CPU, X_accessor<CPU>, DATA>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xE0;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, compare_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xE4;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, compare_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xEC;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, compare_x>(cpu, MNEMONIC);
	}
};

} // namespace cpx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
