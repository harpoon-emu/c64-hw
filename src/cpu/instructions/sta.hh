#ifndef CPU_INSTRUCTIONS_STA_HH
#define CPU_INSTRUCTIONS_STA_HH

#include "write_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sta {

static constexpr const char *MNEMONIC = "STA";

template<typename CPU, typename DATA>
using store_a = store_register<CPU, std::uint8_t, A_accessor<CPU>, DATA>;

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x85;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x95;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x8D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x9D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x99;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x81;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x91;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_write_factory<CPU, store_a>(cpu, MNEMONIC);
	}
};

} // namespace sta
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
