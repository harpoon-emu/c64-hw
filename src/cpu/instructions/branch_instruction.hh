#ifndef CPU_INSTRUCTIONS_BRANCH_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_BRANCH_INSTRUCTION_HH

#include "disassembler.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, typename FLAG, bool V>
class branch_on : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		CPU *cpu = instruction_step_read<CPU>::get_cpu();
		FLAG f(cpu, this);

		if (f.get() == V) {
			std::uint32_t delay = 1;
			std::int16_t pc = static_cast<std::int16_t>(cpu->get_PC());
			std::int8_t offset
			    = static_cast<std::int8_t>(cpu->get_internal_memory_access().b.current);
			cpu->set_PC(static_cast<std::uint16_t>(pc + offset));
			delay++;
			if ((pc & 0xFF) != (cpu->get_PC() & 0xFF)) {
				delay++;
			}
			instruction_step_read<CPU>::set_delay(delay);
		}
		cpu->fetch_opcode();
	}
};

template<typename CPU, typename FLAG, bool V>
harpoon::execution::instruction relative_branch_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(cpu,
	                                       {make_instruction_step<fetch_program_code<CPU>>(),
	                                        make_instruction_step<branch_on<CPU, FLAG, V>>()},
	                                       disassembler::relative(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
