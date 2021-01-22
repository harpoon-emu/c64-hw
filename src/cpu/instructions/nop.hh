#ifndef CPU_INSTRUCTIONS_NOP_HH
#define CPU_INSTRUCTIONS_NOP_HH

#include "disassembler.hh"
#include "instruction_step.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace nop {

static constexpr const char *MNEMONIC = "NOP";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xEA;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(cpu,
		                                       {make_instruction_step<internal_read<CPU>>(),
		                                        make_instruction_step<internal_read<CPU>>()},
		                                       disassembler::implied(MNEMONIC));
	}
};

} // namespace nop
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
