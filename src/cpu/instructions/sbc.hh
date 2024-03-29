#ifndef CPU_INSTRUCTIONS_SBC_HH
#define CPU_INSTRUCTIONS_SBC_HH

#include "arith_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sbc {

static constexpr const char *MNEMONIC = "SBC";

template<typename CPU, typename DATA>
using arith_sbc = accumulator_arith<CPU, DATA, sbc_operation<CPU, true>>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0xE9;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xE5;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xF5;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xED;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xFD;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0xF9;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0xE1;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0xF1;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, arith_sbc>(cpu, MNEMONIC);
	}
};

} // namespace sbc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
