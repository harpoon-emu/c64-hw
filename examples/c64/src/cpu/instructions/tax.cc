#include "tax.hh"

#include "../mos_6510.hh"
#include "read_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {
namespace tax {

harpoon::execution::instruction implied::factory(harpoon::execution::processing_unit *cpu) {
	return transfer_register_factory<std::uint8_t, &mos_6510::get_A, &mos_6510::set_Y, true>(cpu);
}

} // namespace tax
} // namespace instructions
} // namespace cpu
} // namespace commodore