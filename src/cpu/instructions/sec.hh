#ifndef CPU_INSTRUCTIONS_SEC_HH
#define CPU_INSTRUCTIONS_SEC_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sec {

static constexpr const char *MNEMONIC = "SEC";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x38;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_C_accessor<CPU>, true>(cpu, MNEMONIC);
	}
};

} // namespace sec
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
