#ifndef CPU_INSTRUCTIONS_BVC_HH
#define CPU_INSTRUCTIONS_BVC_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bvc {

static constexpr const char *MNEMONIC = "BVC";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0x50;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_V_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace bvc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
