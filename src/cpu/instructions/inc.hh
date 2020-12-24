#ifndef CPU_INSTRUCTIONS_INC_HH
#define CPU_INSTRUCTIONS_INC_HH

#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace inc {

static constexpr const char *MNEMONIC = "INC";

template<typename CPU, typename DATA>
using arith_inc = rmw_arith<CPU, DATA, inc_operation<CPU, std::uint8_t, true>>;

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xE6;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_modify_factory<CPU, arith_inc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xF6;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_modify_factory<CPU, arith_inc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xEE;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_modify_factory<CPU, arith_inc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xFE;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_modify_factory<CPU, arith_inc>(cpu, MNEMONIC);
	}
};

} // namespace inc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
