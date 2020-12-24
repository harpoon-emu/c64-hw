#ifndef CPU_INSTRUCTIONS_LDA_HH
#define CPU_INSTRUCTIONS_LDA_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace lda {

static constexpr const char *MNEMONIC = "LDA";

template<typename CPU, typename DATA>
using load_a = load_register<CPU, std::uint8_t, A_accessor<CPU>, DATA, true>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xA9;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xA5;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xB5;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xAD;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xBD;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xB9;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0xA1;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0xB1;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, load_a>(cpu, MNEMONIC);
	}
};

} // namespace lda
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
