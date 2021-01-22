#ifndef CPU_INSTRUCTIONS_ADC_HH
#define CPU_INSTRUCTIONS_ADC_HH

#include "arith_instruction.hh"
#include "read_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace adc {

static constexpr const char *MNEMONIC = "ADC";

template<typename CPU, typename DATA>
using arith_adc = accumulator_arith<CPU, DATA, adc_operation<CPU, true>>;

template<typename CPU>
struct immediate {
	static constexpr const std::uint8_t OPCODE = 0x69;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return immediate_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x65;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x75;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x6D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_x {
	static constexpr const std::uint8_t OPCODE = 0x7D;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_x_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute_y {
	static constexpr const std::uint8_t OPCODE = 0x79;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_y_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_x {
	static constexpr const std::uint8_t OPCODE = 0x61;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_x_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct indirect_y {
	static constexpr const std::uint8_t OPCODE = 0x71;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return indirect_y_read_factory<CPU, arith_adc>(cpu, MNEMONIC);
	}
};

} // namespace adc
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
