#ifndef CPU_INSTRUCTIONS_CLC_HH
#define CPU_INSTRUCTIONS_CLC_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace clc {

static constexpr const char *MNEMONIC = "CLC";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x18;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_C_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace clc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
