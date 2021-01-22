#ifndef CPU_INSTRUCTIONS_BIT_HH
#define CPU_INSTRUCTIONS_BIT_HH

#include "arith_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bit {

static constexpr const char *MNEMONIC = "BIT";

template<typename CPU, typename DATA>
using arith_bit = accumulator_arith<CPU, DATA, bit_operation<CPU>>;

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x24;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, arith_bit>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x2C;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, arith_bit>(cpu, MNEMONIC);
	}
};

} // namespace bit
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
