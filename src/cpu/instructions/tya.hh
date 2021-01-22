#ifndef CPU_INSTRUCTIONS_TYA_HH
#define CPU_INSTRUCTIONS_TYA_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tya {

static constexpr const char *MNEMONIC = "TYA";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x98;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return transfer_register_factory<CPU, std::uint8_t, Y_accessor<CPU>, A_accessor<CPU>, true>(
		    cpu, MNEMONIC);
	}
};

} // namespace tya
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
