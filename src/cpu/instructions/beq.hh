#ifndef CPU_INSTRUCTIONS_BEQ_HH
#define CPU_INSTRUCTIONS_BEQ_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace beq {

static constexpr const char *MNEMONIC = "BEQ";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0xF0;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_Z_accessor<CPU>, true>(cpu, MNEMONIC);
	}
};

} // namespace beq
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
