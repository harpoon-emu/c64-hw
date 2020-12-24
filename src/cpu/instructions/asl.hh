#ifndef CPU_INSTRUCTIONS_ASL_HH
#define CPU_INSTRUCTIONS_ASL_HH

#include "arith_instruction.hh"
#include "modify_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace asl {

static constexpr const char *MNEMONIC = "ASL";

template<typename CPU, typename DATA>
using arith_asl = rmw_arith<CPU, DATA, asl_operation<CPU, true>>;

template<typename CPU>
struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x0A;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return accumulator_arith_factory<CPU, asl_operation<CPU, true>>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x06;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_modify_factory<CPU, arith_asl>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x16;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_modify_factory<CPU, arith_asl>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x0E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_modify_factory<CPU, arith_asl>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x1E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_modify_factory<CPU, arith_asl>(cpu, MNEMONIC);
	}
};

} // namespace asl
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
