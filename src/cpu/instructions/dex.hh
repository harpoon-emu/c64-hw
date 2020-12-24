#ifndef CPU_INSTRUCTIONS_DEX_HH
#define CPU_INSTRUCTIONS_DEX_HH

#include "arith_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace dex {

static constexpr const char *MNEMONIC = "DEX";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xCA;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return implied_arith_factory<CPU, X_accessor<CPU>, dec_operation<CPU, std::uint8_t, true>>(
		    cpu, MNEMONIC);
	}
};

} // namespace dex
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
