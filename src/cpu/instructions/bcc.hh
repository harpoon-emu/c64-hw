#ifndef CPU_INSTRUCTIONS_BCC_HH
#define CPU_INSTRUCTIONS_BCC_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bcc {

static constexpr const char *MNEMONIC = "BCC";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0x90;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_C_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace bcc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
