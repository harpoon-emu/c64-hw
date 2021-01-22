#ifndef CPU_INSTRUCTIONS_LDX_HH
#define CPU_INSTRUCTIONS_LDX_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ldx {

static constexpr const char *MNEMONIC = "LDX";

template<typename CPU, typename DATA>
using load_x = load_register<CPU, std::uint8_t, X_accessor<CPU>, DATA, true>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xA2;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, load_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xA6;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, load_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_y {
	static constexpr const std::uint8_t OPCODE = 0xB6;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_y_read_factory<CPU, load_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xAE;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, load_x>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xBE;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, load_x>(cpu, MNEMONIC);
	}
};

} // namespace ldx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
