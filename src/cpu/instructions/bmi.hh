#ifndef CPU_INSTRUCTIONS_BMI_HH
#define CPU_INSTRUCTIONS_BMI_HH

#include "branch_instruction.hh"

#include <harpoon/execution/instruction.hh>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace bmi {

static constexpr const char *MNEMONIC = "BMI";

template<typename CPU>
struct relative {
	static constexpr const std::uint8_t OPCODE = 0x30;
	static harpoon::execution::instruction factory(CPU *cpu) {
		return relative_branch_factory<CPU, flag_N_accessor<CPU>, true>(cpu, MNEMONIC);
	}
};

} // namespace bmi
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
