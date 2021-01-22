#ifndef CPU_INSTRUCTIONS_AND_HH
#define CPU_INSTRUCTIONS_AND_HH

#include "arith_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace and_ {

static constexpr const char *MNEMONIC = "AND";

template<typename CPU, typename DATA>
using arith_and = accumulator_arith<CPU, DATA, and_operation<CPU, true>>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0x29;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x25;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x35;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x2D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x3D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x39;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x21;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x31;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, arith_and>(cpu, MNEMONIC);
	}
};

} // namespace and_
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
