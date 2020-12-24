#ifndef CPU_INSTRUCTIONS_CLV_HH
#define CPU_INSTRUCTIONS_CLV_HH

#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace clv {

static constexpr const char *MNEMONIC = "CLV";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xB8;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return set_flag_factory<CPU, flag_V_accessor<CPU>, false>(cpu, MNEMONIC);
	}
};

} // namespace clv
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
