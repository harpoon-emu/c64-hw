#ifndef CPU_INSTRUCTIONS_SED_HH
#define CPU_INSTRUCTIONS_SED_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sed {

static constexpr const char *MNEMONIC = "SED";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xF8;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_D_accessor<CPU>, true>(cpu, MNEMONIC);
	}
};

} // namespace sed
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
