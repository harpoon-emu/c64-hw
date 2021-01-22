#ifndef CPU_INSTRUCTIONS_CLD_HH
#define CPU_INSTRUCTIONS_CLD_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace cld {

static constexpr const char *MNEMONIC = "CLD";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xD8;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_D_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace cld
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
