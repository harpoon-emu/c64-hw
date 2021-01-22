#ifndef CPU_INSTRUCTIONS_TXS_HH
#define CPU_INSTRUCTIONS_TXS_HH

#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace txs {

static constexpr const char *MNEMONIC = "TXS";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x9A;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return transfer_register_factory<CPU, std::uint8_t, X_accessor<CPU>, SP_accessor<CPU>,
		                                 false>(cpu, MNEMONIC);
	}
};

} // namespace txs
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
