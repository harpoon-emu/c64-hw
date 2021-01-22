#ifndef CPU_INSTRUCTIONS_BPL_HH
#define CPU_INSTRUCTIONS_BPL_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bpl {

static constexpr const char *MNEMONIC = "BPL";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0x10;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_N_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace bpl
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
