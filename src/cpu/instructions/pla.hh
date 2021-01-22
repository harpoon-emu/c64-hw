#ifndef CPU_INSTRUCTIONS_PLA_HH
#define CPU_INSTRUCTIONS_PLA_HH

#include "arith_instruction.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace pla {

static constexpr const char *MNEMONIC = "PLA";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x68;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_pull<CPU, A_accessor<CPU>, true>>(),
		    },
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace pla
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
