#ifndef CPU_INSTRUCTIONS_ROL_HH
#define CPU_INSTRUCTIONS_ROL_HH

#include "arith_instruction.hh"
#include "modify_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace rol {

static constexpr const char *MNEMONIC = "ROL";

template<typename CPU, typename DATA>
using arith_rol = rmw_arith<CPU, DATA, rol_operation<CPU, true>>;

template<typename CPU>
struct accumulator {
	static constexpr const std::uint8_t OPCODE = 0x2A;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return accumulator_arith_factory<CPU, rol_operation<CPU, true>>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x26;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_modify_factory<CPU, arith_rol>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x36;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_modify_factory<CPU, arith_rol>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x2E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_modify_factory<CPU, arith_rol>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x3E;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_modify_factory<CPU, arith_rol>(cpu, MNEMONIC);
	}
};

} // namespace rol
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
