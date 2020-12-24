#ifndef CPU_INSTRUCTIONS_ROR_HH
#define CPU_INSTRUCTIONS_ROR_HH

#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ror {

static constexpr const char *MNEMONIC = "ROR";

template<typename CPU, typename DATA>
using arith_ror = rmw_arith<CPU, DATA, ror_operation<CPU, true>>;

template<typename CPU>
struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x6A;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return accumulator_arith_factory<CPU, ror_operation<CPU, true>>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x66;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_modify_factory<CPU, arith_ror>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x76;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_modify_factory<CPU, arith_ror>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x6E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_modify_factory<CPU, arith_ror>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x7E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_modify_factory<CPU, arith_ror>(cpu, MNEMONIC);
	}
};

} // namespace ror
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
