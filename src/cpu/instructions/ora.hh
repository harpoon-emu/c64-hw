#ifndef CPU_INSTRUCTIONS_ORA_HH
#define CPU_INSTRUCTIONS_ORA_HH

#include "arith_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace ora {

static constexpr const char *MNEMONIC = "ORA";

template<typename CPU, typename DATA>
using arith_ora = accumulator_arith<CPU, DATA, or_operation<CPU, true>>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0x09;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x05;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x15;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x0D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x1D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x19;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x01;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x11;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, arith_ora>(cpu, MNEMONIC);
	}
};

} // namespace ora
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
