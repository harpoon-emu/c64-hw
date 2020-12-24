#ifndef CPU_INSTRUCTIONS_INSTRUCTION_STEP_HH
#define CPU_INSTRUCTIONS_INSTRUCTION_STEP_HH

#include "cpu_accessor.hh"
#include "disassembler.hh"

#include <harpoon/execution/instruction.hh>

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU>
class instruction_step {
public:
	instruction_step(const harpoon::execution::instruction &instruction)
	    : _instruction{instruction} {
		_cpu = static_cast<CPU *>(instruction.get_processing_unit());
	}

	virtual std::uint32_t check() = 0;
	virtual std::uint32_t step() {
		execute();
		return _delay;
	}
	virtual void execute() = 0;

	void set_delay(std::uint32_t d) {
		_delay = d;
	}

protected:
	CPU *get_cpu() const {
		return _cpu;
	}

	template<typename T>
	void update_flag_Z(T v) {
		get_cpu()->get_registers().P.Z() = (v == 0);
	}

	template<typename T>
	void update_flag_N(T v) {
		T h = 1 << ((sizeof(T) * 8) - 1);
		get_cpu()->get_registers().P.N() = ((v & h) == h);
	}

	template<typename T>
	void update_flags_NZ(T v) {
		update_flag_Z(v);
		update_flag_N(v);
	}

private:
	const harpoon::execution::instruction _instruction{};
	CPU *_cpu{};
	std::uint32_t _delay{1};
};

template<typename CPU>
class instruction_step_read : public instruction_step<CPU> {
public:
	using instruction_step<CPU>::instruction_step;

	virtual std::uint32_t check() override {
		return 0;
	}
};

template<typename CPU>
class instruction_step_fetch_next : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual std::uint32_t step() override {
		instruction_step_read<CPU>::get_cpu()->fetch_opcode();
		return instruction_step_read<CPU>::step();
	}
};

template<typename CPU>
class instruction_step_write : public instruction_step<CPU> {
public:
	using instruction_step<CPU>::instruction_step;

	virtual std::uint32_t check() override {
		return 0;
	}
};

template<typename CPU>
class internal_read : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {}
};

template<typename CPU>
class internal_write : public instruction_step_write<CPU> {
public:
	using instruction_step_write<CPU>::instruction_step_write;

	virtual void execute() override {}
};

template<typename CPU>
class fetch_program_code : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		instruction_step_read<CPU>::get_cpu()->internal_read_program_code();
	}
};

template<typename CPU, bool x_index>
class fetch_indirect_pointer : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		instruction_step_read<CPU>::get_cpu()->fetch_indirect_pointer(x_index);
	}
};

template<typename CPU, typename REG, bool update_nz>
class stack_pull : public instruction_step_read<CPU> {
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		std::uint8_t v;
		REG reg(instruction_step_read<CPU>::get_cpu(), this);
		instruction_step_read<CPU>::get_cpu()->stack_pull(v);
		reg.set(v);
		if (update_nz) {
			instruction_step_read<CPU>::update_flags_NZ(v);
		}
	}
};

template<typename CPU, typename REG>
class stack_push : public instruction_step_write<CPU> {
	using instruction_step_write<CPU>::instruction_step_write;

	virtual void execute() override {
		REG reg(instruction_step_write<CPU>::get_cpu(), this);
		std::uint8_t v = reg.get();
		instruction_step_write<CPU>::get_cpu()->stack_push(v);
	}
};

template<typename CPU, typename FLAG, bool value>
class set_flag : public instruction_step_read<CPU> {
	using instruction_step_read<CPU>::instruction_step_read;

	virtual void execute() override {
		FLAG flag(instruction_step_read<CPU>::get_cpu(), this);
		flag.set(value);
	}
};

template<typename T>
std::uint32_t check_fn(const harpoon::execution::instruction &instruction) {
	T step(instruction);
	return step.check();
}

template<typename T>
std::uint32_t step_fn(const harpoon::execution::instruction &instruction) {
	T step(instruction);
	return step.step();
}

template<typename T>
harpoon::execution::instruction::step_handlers make_instruction_step() {
	return {check_fn<T>, step_fn<T>};
}

template<typename CPU, typename FLAG, bool value>
harpoon::execution::instruction set_flag_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(cpu,
	                                       {
	                                           make_instruction_step<set_flag<CPU, FLAG, value>>(),
	                                       },
	                                       disassembler::implied(mnemonic));
}

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
