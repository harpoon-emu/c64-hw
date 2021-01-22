#ifndef CPU_INSTRUCTIONS_CLI_HH
#define CPU_INSTRUCTIONS_CLI_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cli {

static constexpr const char *MNEMONIC = "CLI";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x58;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_I_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace cli
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
