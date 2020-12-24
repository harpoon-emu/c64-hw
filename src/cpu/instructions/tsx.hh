#ifndef CPU_INSTRUCTIONS_TSX_HH
#define CPU_INSTRUCTIONS_TSX_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tsx {

static constexpr const char *MNEMONIC = "TSX";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xBA;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return transfer_register_factory<CPU, std::uint8_t, SP_accessor<CPU>, X_accessor<CPU>,
		                                 true>(cpu, MNEMONIC);
	}
};

} // namespace tsx
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
