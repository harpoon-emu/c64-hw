#ifndef CPU_INSTRUCTIONS_MODIFY_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_MODIFY_INSTRUCTION_HH

#include "instruction_step.hh"
#include "read_instruction.hh"

#include "harpoon/c64-hw/cpu/mos_6510.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_modify_factory(harpoon::execution::processing_unit *cpu,
                                                         const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<load_latch<&instruction_step::fetch_zero_page>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_zero_page>>(),
	    },
	    disassembler::zero_page(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_x_modify_factory(harpoon::execution::processing_unit *cpu,
                                                           const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<
	            load_latch<&instruction_step::fetch_zero_page_reg<&mos_6510::get_X>>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_zero_page_reg<&mos_6510::get_X>>>(),
	    },
	    disassembler::zero_page_x(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction zero_page_y_modify_factory(harpoon::execution::processing_unit *cpu,
                                                           const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<
	            load_latch<&instruction_step::fetch_zero_page_reg<&mos_6510::get_Y>>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_zero_page_reg<&mos_6510::get_X>>>(),
	    },
	    disassembler::zero_page_y(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_modify_factory(harpoon::execution::processing_unit *cpu,
                                                        const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<load_latch<&instruction_step::fetch_absolute>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_absolute>>(),
	    },
	    disassembler::absolute(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_x_modify_factory(harpoon::execution::processing_unit *cpu,
                                                          const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<
	            load_latch<&instruction_step::fetch_absolute_reg<&mos_6510::get_X>>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_absolute_reg<&mos_6510::get_X>>>(),
	    },
	    disassembler::absolute_x(mnemonic));
}

template<template<void (instruction_step::*store)(std::uint8_t)> class I>
harpoon::execution::instruction absolute_y_modify_factory(harpoon::execution::processing_unit *cpu,
                                                          const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<fetch_program_code>(),
	        make_instruction_step<internal_read>(),
	        make_instruction_step<
	            load_latch<&instruction_step::fetch_absolute_reg<&mos_6510::get_Y>>>(),
	        make_instruction_step<internal_write>(),
	        make_instruction_step<I<&instruction_step::store_absolute_reg<&mos_6510::get_Y>>>(),
	    },
	    disassembler::absolute_y(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
