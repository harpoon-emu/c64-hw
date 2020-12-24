#ifndef CPU_INSTRUCTIONS_BNE_HH
#define CPU_INSTRUCTIONS_BNE_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bne {

static constexpr const char *MNEMONIC = "BNE";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0xD0;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_Z_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace bne
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
