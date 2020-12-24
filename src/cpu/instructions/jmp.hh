#ifndef CPU_INSTRUCTIONS_JMP_HH
#define CPU_INSTRUCTIONS_JMP_HH

#include "disassembler.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace jmp {

static constexpr const char *MNEMONIC = "JMP";

template<typename CPU>
class fetch_pcl : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		CPU *cpu = instruction_step_read<CPU>::get_cpu();
		std::uint8_t v;

		cpu->get_memory()->get(cpu->get_internal_memory_access().w, v);
		cpu->set_latch(v);
	}
};

template<typename CPU>
class fetch_pch : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		CPU *cpu = instruction_step_read<CPU>::get_cpu();
		std::uint8_t v;
		std::uint16_t a = static_cast<std::uint16_t>(cpu->get_internal_memory_access().b.h << 8)
		                  | static_cast<std::uint8_t>(cpu->get_internal_memory_access().b.l + 1);

		cpu->get_memory()->get(a, v);
		cpu->set_PCL(cpu->get_latch());
		cpu->set_PCH(v);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x4C;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(
		    cpu,
		    {
		        make_instruction_step<fetch_program_code<CPU>>(),
		        make_instruction_step<load_register<CPU, std::uint16_t, PC_accessor<CPU>,
		                                            program_code_accessor<CPU>, false>>(),
		    },
		    disassembler::absolute(MNEMONIC));
	}
};

template<typename CPU>
struct indirect {
	static constexpr const std::uint8_t OPCODE = 0x6C;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return harpoon::execution::instruction(cpu,
		                                       {
		                                           make_instruction_step<fetch_program_code<CPU>>(),
		                                           make_instruction_step<fetch_program_code<CPU>>(),
		                                           make_instruction_step<fetch_pcl<CPU>>(),
		                                           make_instruction_step<fetch_pch<CPU>>(),
		                                       },
		                                       disassembler::indirect(MNEMONIC));
	}
};

} // namespace jmp
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
