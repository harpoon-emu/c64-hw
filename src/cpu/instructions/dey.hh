#ifndef CPU_INSTRUCTIONS_DEY_HH
#define CPU_INSTRUCTIONS_DEY_HH

#include "arith_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace dey {

static constexpr const char *MNEMONIC = "DEY";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0x88;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return implied_arith_factory<CPU, Y_accessor<CPU>, dec_operation<CPU, std::uint8_t, true>>(
		    cpu, MNEMONIC);
	}
};

} // namespace dey
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
