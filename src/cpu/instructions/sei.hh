#ifndef CPU_INSTRUCTIONS_SEI_HH
#define CPU_INSTRUCTIONS_SEI_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sei {

static constexpr const char *MNEMONIC = "SEI";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x78;

	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_I_accessor<CPU>, true>(cpu, MNEMONIC);
	}
};

} // namespace sei
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
