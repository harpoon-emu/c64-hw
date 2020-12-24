#ifndef CPU_INSTRUCTIONS_BVS_HH
#define CPU_INSTRUCTIONS_BVS_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bvs {

static constexpr const char *MNEMONIC = "BVS";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0x70;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_V_accessor<CPU>, true>(cpu, MNEMONIC);
	}
};

} // namespace bvs
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
