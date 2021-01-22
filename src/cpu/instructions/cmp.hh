#ifndef CPU_INSTRUCTIONS_CMP_HH
#define CPU_INSTRUCTIONS_CMP_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cmp {

static constexpr const char *MNEMONIC = "CMP";

template<typename CPU, typename DATA>
using compare_a = compare_register<CPU, A_accessor<CPU>, DATA>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xC9;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xC5;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xD5;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xCD;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xDD;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xD9;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0xC1;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0xD1;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, compare_a>(cpu, MNEMONIC);
	}
};

} // namespace cmp
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
