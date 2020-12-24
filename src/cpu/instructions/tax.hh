#ifndef CPU_INSTRUCTIONS_TAX_HH
#define CPU_INSTRUCTIONS_TAX_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace tax {

static constexpr const char *MNEMONIC = "TAX";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xAA;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return transfer_register_factory<CPU, std::uint8_t, A_accessor<CPU>, X_accessor<CPU>, true>(
		    cpu, MNEMONIC);
	}
};

} // namespace tax
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
