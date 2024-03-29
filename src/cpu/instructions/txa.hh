#ifndef CPU_INSTRUCTIONS_TXA_HH
#define CPU_INSTRUCTIONS_TXA_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace txa {

static constexpr const char *MNEMONIC = "TXA";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x8A;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return transfer_register_factory<CPU, std::uint8_t, X_accessor<CPU>, A_accessor<CPU>, true>(
		    cpu, MNEMONIC);
	}
};

} // namespace txa
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
