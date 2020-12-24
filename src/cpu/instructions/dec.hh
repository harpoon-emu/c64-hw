#ifndef CPU_INSTRUCTIONS_DEC_HH
#define CPU_INSTRUCTIONS_DEC_HH

#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace dec {

static constexpr const char *MNEMONIC = "DEC";

template<typename CPU, typename DATA>
using arith_dec = rmw_arith<CPU, DATA, dec_operation<CPU, std::uint8_t, true>>;

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0xC6;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_modify_factory<CPU, arith_dec>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0xD6;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_modify_factory<CPU, arith_dec>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0xCE;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_modify_factory<CPU, arith_dec>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0xDE;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_modify_factory<CPU, arith_dec>(cpu, MNEMONIC);
	}
};

} // namespace dec
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
