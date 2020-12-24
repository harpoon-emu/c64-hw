#ifndef CPU_INSTRUCTIONS_BRK_HH
#define CPU_INSTRUCTIONS_BRK_HH

#include "disassembler.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace brk {

static constexpr const char *MNEMONIC = "BRK";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x00;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {make_instruction_step<fetch_program_code<CPU>>(),
		     make_instruction_step<internal_read<CPU>>(),
		     make_instruction_step<stack_push<CPU, PCH_accessor<CPU>>>(),
		     make_instruction_step<stack_push<CPU, PCL_accessor<CPU>>>(),
		     make_instruction_step<stack_push<CPU, P_accessor<CPU>>>(),
		     make_instruction_step<load_register<CPU, std::uint8_t, PCL_accessor<CPU>,
		                                         value_accessor<CPU, std::uint8_t, 0xFE>, false>>(),
		     make_instruction_step<
		         load_register<CPU, std::uint8_t, PCH_accessor<CPU>,
		                       value_accessor<CPU, std::uint8_t, 0xFF>, false>>()},
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace brk
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
