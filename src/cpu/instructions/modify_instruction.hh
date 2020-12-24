#ifndef CPU_INSTRUCTIONS_MODIFY_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_MODIFY_INSTRUCTION_HH

#include "instruction_step.hh"
#include "read_instruction.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_modify_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<load_latch<CPU, zero_page_accessor<CPU>>>(),
	        make_instruction_step<internal_write<CPU>>(),
	        make_instruction_step<I<CPU, zero_page_accessor<CPU>>>(),
	    },
	    disassembler::zero_page(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_x_modify_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<
	            load_latch<CPU, indexed_zero_page_accessor<CPU, X_accessor<CPU>>>>(),
	        make_instruction_step<internal_write<CPU>>(),
	        make_instruction_step<I<CPU, indexed_zero_page_accessor<CPU, X_accessor<CPU>>>>(),
	    },
	    disassembler::zero_page_x(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_y_modify_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<
	            load_latch<CPU, indexed_zero_page_accessor<CPU, Y_accessor<CPU>>>>(),
	        make_instruction_step<internal_write<CPU>>(),
	        make_instruction_step<I<CPU, indexed_zero_page_accessor<CPU, X_accessor<CPU>>>>(),
	    },
	    disassembler::zero_page_y(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_modify_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<load_latch<CPU, absolute_accessor<CPU>>>(),
	        make_instruction_step<internal_write<CPU>>(),
	        make_instruction_step<I<CPU, absolute_accessor<CPU>>>(),
	    },
	    disassembler::absolute(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_x_modify_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<
	            load_latch<CPU, indexed_absolute_accessor<CPU, X_accessor<CPU>>>>(),
	        make_instruction_step<internal_write<CPU>>(),
	        make_instruction_step<I<CPU, indexed_absolute_accessor<CPU, X_accessor<CPU>>>>(),
	    },
	    disassembler::absolute_x(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_y_modify_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<
	            load_latch<CPU, indexed_absolute_accessor<CPU, Y_accessor<CPU>>>>(),
	        make_instruction_step<internal_write<CPU>>(),
	        make_instruction_step<I<CPU, indexed_absolute_accessor<CPU, Y_accessor<CPU>>>>(),
	    },
	    disassembler::absolute_y(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
