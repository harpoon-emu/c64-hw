#ifndef CPU_INSTRUCTIONS_LDY_HH
#define CPU_INSTRUCTIONS_LDY_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ldy {

static constexpr const char *MNEMONIC = "LDY";

template<typename CPU, typename DATA>
using load_y = load_register<CPU, std::uint8_t, Y_accessor<CPU>, DATA, true>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xA0;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, load_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xA4;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, load_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xB4;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, load_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xAC;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, load_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xBC;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, load_y>(cpu, MNEMONIC);
	}
};

} // namespace ldy
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
