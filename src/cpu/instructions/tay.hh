#ifndef CPU_INSTRUCTIONS_TAY_HH
#define CPU_INSTRUCTIONS_TAY_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tay {

static constexpr const char *MNEMONIC = "TAY";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xA8;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return transfer_register_factory<CPU, std::uint8_t, A_accessor<CPU>, Y_accessor<CPU>, true>(
		    cpu, MNEMONIC);
	}
};

} // namespace tay
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
