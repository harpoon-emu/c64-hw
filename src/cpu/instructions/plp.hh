#ifndef CPU_INSTRUCTIONS_PLP_HH
#define CPU_INSTRUCTIONS_PLP_HH

#include "arith_instruction.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace plp {

static constexpr const char *MNEMONIC = "PLP";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x28;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_pull<CPU, P_accessor<CPU>, false>>(),
		    },
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace plp
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
