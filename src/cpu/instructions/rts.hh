#ifndef CPU_INSTRUCTIONS_RTS_HH
#define CPU_INSTRUCTIONS_RTS_HH

#include "arith_instruction.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rts {

static constexpr const char *MNEMONIC = "RTS";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x60;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_pull<CPU, PCL_accessor<CPU>, false>>(),
		        make_instruction_step<stack_pull<CPU, PCH_accessor<CPU>, false>>(),
		        make_instruction_step<implied_arith16<CPU, PC_accessor<CPU>,
		                                              inc_operation<CPU, std::uint16_t, false>>>(),
		    },
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace rts
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
