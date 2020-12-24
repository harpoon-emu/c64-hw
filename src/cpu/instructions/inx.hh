#ifndef CPU_INSTRUCTIONS_INX_HH
#define CPU_INSTRUCTIONS_INX_HH

#include "arith_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace inx {

static constexpr const char *MNEMONIC = "INX";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xE8;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return implied_arith_factory<CPU, X_accessor<CPU>, inc_operation<CPU, std::uint8_t, true>>(
		    cpu, MNEMONIC);
	}
};

} // namespace inx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
