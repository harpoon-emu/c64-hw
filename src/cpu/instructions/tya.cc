#include "tya.hh"

#include "read_instruction.hh"

#include "harpoon/c64-hw/cpu/mos_6510.hh"

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tya {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return transfer_register_factory<std::uint8_t, &mos_6510::get_Y, &mos_6510::set_A, true>(
	    cpu, MNEMONIC);
}

} // namespace tya
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64
