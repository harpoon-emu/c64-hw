#ifndef CPU_INSTRUCTIONS_STY_HH
#define CPU_INSTRUCTIONS_STY_HH

#include "write_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace sty {

static constexpr const char *MNEMONIC = "STY";

template<typename CPU, typename DATA>
using store_y = store_register<CPU, std::uint8_t, Y_accessor<CPU>, DATA>;

template<typename CPU>
struct zero_page {
	static constexpr const std::uint8_t OPCODE = 0x84;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_write_factory<CPU, store_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct zero_page_x {
	static constexpr const std::uint8_t OPCODE = 0x94;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return zero_page_x_write_factory<CPU, store_y>(cpu, MNEMONIC);
	}
};

template<typename CPU>
struct absolute {
	static constexpr const std::uint8_t OPCODE = 0x8C;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return absolute_write_factory<CPU, store_y>(cpu, MNEMONIC);
	}
};

} // namespace sty
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
