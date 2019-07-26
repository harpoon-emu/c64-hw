#include "pha.hh"

#include "disassembler.hh"
#include "read_instruction.hh"

#include "harpoon/c64-hw/cpu/mos_6510.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace pha {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<internal_read>(),
	        make_instruction_step<stack_push<&mos_6510::get_A>>(),
	    },
	    disassembler::implied(MNEMONIC));
}

} // namespace pha
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
