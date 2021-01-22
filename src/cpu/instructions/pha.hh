#ifndef CPU_INSTRUCTIONS_PHA_HH
#define CPU_INSTRUCTIONS_PHA_HH

#include "disassembler.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace pha {

static constexpr const char *MNEMONIC = "PHA";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x48;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<internal_read<CPU>>(),
		        make_instruction_step<stack_push<CPU, A_accessor<CPU>>>(),
		    },
		    disassembler::implied(MNEMONIC));
	}
};

} // namespace pha
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
