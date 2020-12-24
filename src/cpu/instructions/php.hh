#ifndef CPU_INSTRUCTIONS_PHP_HH
#define CPU_INSTRUCTIONS_PHP_HH

#include "disassembler.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace php {

static constexpr const char *MNEMONIC = "PHP";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x08;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_push<CPU, P_accessor<CPU>>>(),
		    },
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace php
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
