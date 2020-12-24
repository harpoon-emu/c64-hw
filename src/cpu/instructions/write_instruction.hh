#ifndef CPU_INSTRUCTIONS_WRITE_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_WRITE_INSTRUCTION_HH

#include "data_accessor.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, typename T, typename REG, typename DATA>
class store_register : public instruction_step_write<CPU> {
	using instruction_step_write<CPU>::instruction_step_write;

	virtual void execute() override {
		DATA d(instruction_step_write<CPU>::get_cpu(), this);
		REG r(instruction_step_write<CPU>::get_cpu(), this);
		d.store(r.get());
	}
};

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_write_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<I<CPU, zero_page_accessor<CPU>>>(),
	    },
	    disassembler::zero_page(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I, typename REG, typename D>
harpoon::execution::instruction zero_page_index_write_factory(CPU *cpu,
                                                              const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<I<CPU, indexed_zero_page_accessor<CPU, REG>>>(),
	    },
	    D(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_x_write_factory(CPU *cpu, const std::string &mnemonic) {
	return zero_page_index_write_factory<CPU, I, X_accessor<CPU>, disassembler::zero_page_x>(
	    cpu, mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_y_write_factory(CPU *cpu, const std::string &mnemonic) {
	return zero_page_index_write_factory<CPU, I, Y_accessor<CPU>, disassembler::zero_page_y>(
	    cpu, mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_write_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<I<CPU, absolute_accessor<CPU>>>(),
	    },
	    disassembler::absolute(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I, typename REG, typename D>
harpoon::execution::instruction absolute_index_write_factory(CPU *cpu,
                                                             const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<I<CPU, indexed_absolute_accessor<CPU, REG>>>(),
	    },
	    D(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_x_write_factory(CPU *cpu, const std::string &mnemonic) {
	return absolute_index_write_factory<CPU, I, X_accessor<CPU>, disassembler::absolute_x>(
	    cpu, mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_y_write_factory(CPU *cpu, const std::string &mnemonic) {
	return absolute_index_write_factory<CPU, I, Y_accessor<CPU>, disassembler::absolute_y>(
	    cpu, mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction indirect_x_write_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<internal_read<CPU>>(),
	        make_instruction_step<fetch_indirect_pointer<CPU, true>>(),
	        make_instruction_step<fetch_indirect_pointer<CPU, true>>(),
	        make_instruction_step<I<CPU, indirect_accessor<CPU>>>(),
	    },
	    disassembler::indirect_x(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction indirect_y_write_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_indirect_pointer<CPU, false>>(),
	        make_instruction_step<fetch_indirect_pointer<CPU, false>>(),
	        make_instruction_step<I<CPU, indexed_indirect_accessor<CPU, Y_accessor<CPU>>>>(),
	    },
	    disassembler::indirect_y(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
