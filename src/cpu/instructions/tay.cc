#include "tay.hh"

#include "read_instruction.hh"

#include "harpoon/c64-hw/cpu/mos_6510.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tay {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return transfer_register_factory<std::uint8_t, &mos_6510::get_A, &mos_6510::set_Y, true>(
	    cpu, MNEMONIC);
}

} // namespace tay
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
