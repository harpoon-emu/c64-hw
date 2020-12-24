#ifndef CPU_INSTRUCTIONS_READ_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_READ_INSTRUCTION_HH

#include "data_accessor.hh"
#include "disassembler.hh"
#include "instruction_step.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, typename T, typename REG, typename DATA, bool update_flags>
class load_register : public instruction_step_read<CPU> {
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		T v;
		REG r(instruction_step_read<CPU>::get_cpu(), this);
		DATA d(instruction_step_read<CPU>::get_cpu(), this);
		v = d.fetch(update_flags);
		r.set(v);
	}
};

template<typename CPU, typename DATA>
using load_latch = load_register<CPU, std::uint8_t, latch_accessor<CPU>, DATA, false>;

template<typename CPU, typename T, typename SREG, typename DREG, bool update_flags>
using transfer_register
    = load_register<CPU, T, SREG, register_accessor<CPU, T, DREG>, update_flags>;

template<typename CPU, typename REG, typename DATA>
class compare_register : public instruction_step_read<CPU> {
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		std::uint8_t a, m, r;
		REG reg(instruction_step_read<CPU>::get_cpu(), this);
		DATA d(instruction_step_read<CPU>::get_cpu(), this);

		a = reg.get();
		m = d.fetch(false);
		r = a - m;

		instruction_step_read<CPU>::get_cpu()->get_registers().P.N() = ((r & 0x80) == 0x80);
		instruction_step_read<CPU>::get_cpu()->get_registers().P.Z() = (r == 0x00);
		instruction_step_read<CPU>::get_cpu()->get_registers().P.C() = (a >= m);
	}
};

template<typename CPU, typename T, typename SREG, typename DREG, bool update_flags>
harpoon::execution::instruction transfer_register_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<transfer_register<CPU, T, SREG, DREG, update_flags>>()},
	    disassembler::implied(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction immediate_read_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu, {make_instruction_step<I<CPU, immediate_accessor<CPU, std::uint8_t>>>()},
	    disassembler::immediate(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_read_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<I<CPU, zero_page_accessor<CPU>>>(),
	    },
	    disassembler::zero_page(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I, typename REG, typename D>
harpoon::execution::instruction zero_page_index_read_factory(CPU *cpu,
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
harpoon::execution::instruction zero_page_x_read_factory(CPU *cpu, const std::string &mnemonic) {
	return zero_page_index_read_factory<CPU, I, X_accessor<CPU>, disassembler::zero_page_x>(
	    cpu, mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction zero_page_y_read_factory(CPU *cpu, const std::string &mnemonic) {
	return zero_page_index_read_factory<CPU, I, Y_accessor<CPU>, disassembler::zero_page_y>(
	    cpu, mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_read_factory(CPU *cpu, const std::string &mnemonic) {
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
harpoon::execution::instruction absolute_index_read_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<fetch_program_code<CPU>>(),
	        make_instruction_step<I<CPU, indexed_absolute_accessor<CPU, REG>>>(),
	    },
	    D(mnemonic));
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_x_read_factory(CPU *cpu, const std::string &mnemonic) {
	return absolute_index_read_factory<CPU, I, X_accessor<CPU>, disassembler::absolute_x>(cpu,
	                                                                                      mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction absolute_y_read_factory(CPU *cpu, const std::string &mnemonic) {
	return absolute_index_read_factory<CPU, I, Y_accessor<CPU>, disassembler::absolute_y>(cpu,
	                                                                                      mnemonic);
}

template<typename CPU, template<typename _CPU, typename _DATA> class I>
harpoon::execution::instruction indirect_x_read_factory(CPU *cpu, const std::string &mnemonic) {
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
harpoon::execution::instruction indirect_y_read_factory(CPU *cpu, const std::string &mnemonic) {
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
