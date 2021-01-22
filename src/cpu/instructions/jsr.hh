#ifndef CPU_INSTRUCTIONS_JSR_HH
#define CPU_INSTRUCTIONS_JSR_HH

#include "disassembler.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace jsr {

static constexpr const char *MNEMONIC = "JSR";

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x20;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<fetch_program_code<CPU>>(),
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_push<CPU, PCH_accessor<CPU>>>(),
		        make_instruction_step<stack_push<CPU, PCL_accessor<CPU>>>(),
		        make_instruction_step<load_register<CPU, std::uint16_t, PC_accessor<CPU>,
		                                            program_code_accessor<CPU>, false>>(),
		    },
		    disassembler::absolute(MNEMONIC));
	}
};

} // namespace jsr
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
