#ifndef CPU_INSTRUCTIONS_INSTRUCTION_STEP_OP_HH
#define CPU_INSTRUCTIONS_INSTRUCTION_STEP_OP_HH

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU>
class instruction_step;

template<typename CPU, typename T>
class instruction_step_op {
public:
	instruction_step_op(CPU *cpu, instruction_step<CPU> *step) : _cpu{cpu}, _step{step} {}

	CPU *get_cpu() const {
		return _cpu;
	}

	instruction_step<CPU> *get_instruction_step() const {
		return _step;
	}

	void update_flag_Z(T v) const {
		get_cpu()->get_registers().P.Z() = (v == 0);
	}

	void update_flag_N(T v) const {
		T h = 1 << ((sizeof(T) * 8) - 1);
		get_cpu()->get_registers().P.N() = ((v & h) == h);
	}

	void update_flags_NZ(T v) const {
		update_flag_Z(v);
		update_flag_N(v);
	}

private:
	CPU *_cpu{};
	instruction_step<CPU> *_step{};
};

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
