#ifndef CPU_INSTRUCTIONS_EOR_HH
#define CPU_INSTRUCTIONS_EOR_HH

#include "arith_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace eor {

static constexpr const char *MNEMONIC = "EOR";

template<typename CPU, typename DATA>
using arith_eor = accumulator_arith<CPU, DATA, eor_operation<CPU, true>>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0x49;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x45;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x55;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x4D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x5D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x59;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x41;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x51;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, arith_eor>(cpu, MNEMONIC);
	}
};

} // namespace eor
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
