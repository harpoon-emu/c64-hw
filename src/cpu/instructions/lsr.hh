#ifndef CPU_INSTRUCTIONS_LSR_HH
#define CPU_INSTRUCTIONS_LSR_HH

#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace lsr {

static constexpr const char *MNEMONIC = "LSR";

template<typename CPU, typename DATA>
using arith_lsr = rmw_arith<CPU, DATA, lsr_operation<CPU, true>>;

template<typename CPU>
struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x4A;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return accumulator_arith_factory<CPU, lsr_operation<CPU, true>>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x46;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_modify_factory<CPU, arith_lsr>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x56;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_modify_factory<CPU, arith_lsr>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x4E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_modify_factory<CPU, arith_lsr>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x5E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_modify_factory<CPU, arith_lsr>(cpu, MNEMONIC);
	}
};

} // namespace lsr
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
