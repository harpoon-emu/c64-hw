#ifndef CPU_INSTRUCTIONS_INY_HH
#define CPU_INSTRUCTIONS_INY_HH

#include "arith_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace iny {

static constexpr const char *MNEMONIC = "INY";

template<typename CPU>
struct implied {
	static constexpr const std::uint8_t OPCODE = 0xC8;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return implied_arith_factory<CPU, Y_accessor<CPU>, inc_operation<CPU, std::uint8_t, true>>(
		    cpu, MNEMONIC);
	}
};

} // namespace iny
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
