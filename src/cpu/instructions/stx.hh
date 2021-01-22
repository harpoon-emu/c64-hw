#ifndef CPU_INSTRUCTIONS_STX_HH
#define CPU_INSTRUCTIONS_STX_HH

#include "write_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace stx {

static constexpr const char *MNEMONIC = "STX";

template<typename CPU, typename DATA>
using store_x = store_register<CPU, std::uint8_t, X_accessor<CPU>, DATA>;

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x86;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_write_factory<CPU, store_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_y {
	static constexpr const std::uint8_t OPCODE = 0x96;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_y_write_factory<CPU, store_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x8E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_write_factory<CPU, store_x>(cpu, MNEMONIC);
	}
};

} // namespace stx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
