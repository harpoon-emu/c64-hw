#ifndef CPU_INSTRUCTIONS_RTI_HH
#define CPU_INSTRUCTIONS_RTI_HH

#include "arith_instruction.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rti {

static constexpr const char *MNEMONIC = "RTI";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x40;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_pull<CPU, P_accessor<CPU>, false>>(),
		        make_instruction_step<stack_pull<CPU, PCL_accessor<CPU>, false>>(),
		        make_instruction_step<stack_pull<CPU, PCH_accessor<CPU>, false>>(),
		    },
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace rti
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
