#ifndef CPU_INSTRUCTIONS_ARITH_INSTRUCTION_HH
#define CPU_INSTRUCTIONS_ARITH_INSTRUCTION_HH

#include "disassembler.hh"
#include "instruction_step.hh"
#include "instruction_step_op.hh"

#include <functional>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, typename T>
class arithmetic_operation : public instruction_step_op<CPU, T> {
public:
	using instruction_step_op<CPU, T>::instruction_step_op;
};

template<typename CPU, typename R, typename T>
class unary_arithmetic_operation : public arithmetic_operation<CPU, R> {
public:
	using arithmetic_operation<CPU, R>::arithmetic_operation;

	R calculate(T v1, bool update_flags) {
		return 0;
	}
};

template<typename CPU, typename R, typename T1, typename T2>
class binary_arithmetic_operation : public arithmetic_operation<CPU, R> {
public:
	using arithmetic_operation<CPU, R>::arithmetic_operation;

	R calculate(T1 v1, bool update_flags) {}
};

template<typename CPU, typename T, bool update_flags>
class inc_operation : public unary_arithmetic_operation<CPU, T, T> {
public:
	using unary_arithmetic_operation<CPU, T, T>::unary_arithmetic_operation;

	T calculate(T v) {
		v++;
		if (update_flags) {
			unary_arithmetic_operation<CPU, T, T>::update_flags_NZ(v);
		}
		return v;
	}
};

template<typename CPU, typename T, bool update_flags>
class dec_operation : public unary_arithmetic_operation<CPU, T, T> {
public:
	using unary_arithmetic_operation<CPU, T, T>::unary_arithmetic_operation;

	T calculate(T v) {
		v--;
		if (update_flags) {
			unary_arithmetic_operation<CPU, T, T>::update_flags_NZ(v);
		}
		return v;
	}
};

template<typename CPU, bool update_flags>
class adc_operation
    : public binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t> {
public:
	using binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
	                                  std::uint8_t>::binary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v1, std::uint8_t v2) {
		CPU *cpu
		    = binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t>::get_cpu();
		std::uint8_t x = v1, y = v2;
		std::uint16_t res = {};

		res = x + y;
		if (cpu->get_flag_C()) {
			res++;
		}
		v1 = static_cast<std::uint8_t>(res & 0xff);
		if (update_flags) {
			binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
			                            std::uint8_t>::update_flags_NZ(v1);
			cpu->set_flag_V(((~(x ^ y)) & (x ^ res) & 0x80) == 0x80);
			cpu->set_flag_C(res > 0xff);
		}
		return v1;
	}
};

template<typename CPU, bool update_flags>
class sbc_operation
    : public binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t> {
public:
	using binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
	                                  std::uint8_t>::binary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v1, std::uint8_t v2) {
		CPU *cpu
		    = binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t>::get_cpu();
		std::uint8_t x = v1, y = ~v2;
		std::uint16_t res = {};

		res = x + y;
		if (cpu->get_flag_C()) {
			res++;
		}
		v1 = static_cast<std::uint8_t>(res & 0xff);
		if (update_flags) {
			binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
			                            std::uint8_t>::update_flags_NZ(v1);
			cpu->set_flag_V(((~(x ^ y)) & (x ^ res) & 0x80) == 0x80);
			cpu->set_flag_C(res > 0xff);
		}
		return v1;
	}
};

template<typename CPU, bool update_flags>
class and_operation
    : public binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t> {
public:
	using binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
	                                  std::uint8_t>::binary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v1, std::uint8_t v2) {
		v1 &= v2;
		if (update_flags) {
			binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
			                            std::uint8_t>::update_flags_NZ(v1);
		}
		return v1;
	}
};

template<typename CPU, bool update_flags>
class or_operation
    : public binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t> {
public:
	using binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
	                                  std::uint8_t>::binary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v1, std::uint8_t v2) {
		v1 |= v2;
		if (update_flags) {
			binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
			                            std::uint8_t>::update_flags_NZ(v1);
		}
		return v1;
	}
};

template<typename CPU, bool update_flags>
class eor_operation
    : public binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t> {
public:
	using binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
	                                  std::uint8_t>::binary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v1, std::uint8_t v2) {
		v1 ^= v2;
		if (update_flags) {
			binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
			                            std::uint8_t>::update_flags_NZ(v1);
		}
		return v1;
	}
};

template<typename CPU, bool update_flags>
class asl_operation : public unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t> {
public:
	using unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::unary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v) {
		std::uint8_t x = v;
		v <<= 1;
		if (update_flags) {
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::update_flags_NZ(v);
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::get_cpu()->set_flag_C(
			    (x & 0x80) == 0x80);
		}
		return v;
	}
};

template<typename CPU, bool update_flags>
class lsr_operation : public unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t> {
public:
	using unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::unary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v) {
		std::uint8_t x = v;
		v >>= 1;
		if (update_flags) {
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::update_flags_NZ(v);
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::get_cpu()->set_flag_C(
			    (x & 1) == 1);
		}
		return v;
	}
};

template<typename CPU, bool update_flags>
class rol_operation : public unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t> {
public:
	using unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::unary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v) {

		std::uint8_t x = v;
		v <<= 1;
		v |= unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::get_cpu()->get_flag_C()
		         ? 0x01
		         : 0x00;
		if (update_flags) {
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::update_flags_NZ(v);
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::get_cpu()->set_flag_C(
			    (x & 0x80) == 0x80);
		}
		return v;
	}
};

template<typename CPU, bool update_flags>
class ror_operation : public unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t> {
public:
	using unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::unary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v) {
		std::uint8_t x = v;
		v >>= 1;
		v |= unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::get_cpu()->get_flag_C()
		         ? 0x80
		         : 0x00;
		if (update_flags) {
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::update_flags_NZ(v);
			unary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t>::get_cpu()->set_flag_C(
			    (x & 0x01) == 0x01);
		}
		return v;
	}
};

template<typename CPU>
class bit_operation
    : public binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t> {
public:
	using binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t,
	                                  std::uint8_t>::binary_arithmetic_operation;

	std::uint8_t calculate(std::uint8_t v1, std::uint8_t v2) {
		binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t>::update_flags_NZ(
		    v1 & v2);
		binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t>::get_cpu()
		    ->set_flag_V((v2 & 0x80) == 0x80);
		binary_arithmetic_operation<CPU, std::uint8_t, std::uint8_t, std::uint8_t>::get_cpu()
		    ->set_flag_N((v2 & 0x40) == 0x40);
		return v1;
	}
};

template<typename CPU>
class arith : public instruction_step_read<CPU> {
public:
	using instruction_step_read<CPU>::instruction_step_read;
};

template<typename CPU, typename T, typename REG, typename OP>
class implied_arith : public arith<CPU> {
public:
	using arith<CPU>::arith;

	virtual void execute() override {
		T v;
		REG r(arith<CPU>::get_cpu(), this);
		OP op(arith<CPU>::get_cpu(), this);

		v = r.get();
		r.set(op.calculate(v));
	}
};

template<typename CPU, typename REG, typename OP>
using implied_arith8 = implied_arith<CPU, std::uint8_t, REG, OP>;

template<typename CPU, typename REG, typename OP>
using implied_arith16 = implied_arith<CPU, std::uint16_t, REG, OP>;

template<typename CPU, typename REG, typename OP>
harpoon::execution::instruction implied_arith_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<implied_arith8<CPU, REG, OP>>(),
	    },
	    disassembler::implied(mnemonic));
}

template<typename CPU, typename OP>
harpoon::execution::instruction accumulator_arith_factory(CPU *cpu, const std::string &mnemonic) {
	return harpoon::execution::instruction(
	    cpu,
	    {
	        make_instruction_step<implied_arith8<CPU, A_accessor<CPU>, OP>>(),
	    },
	    disassembler::accumulator(mnemonic));
}

template<typename CPU, typename DATA, typename OP>
class accumulator_arith : public arith<CPU> {
public:
	using arith<CPU>::arith;

	virtual void execute() override {
		std::uint8_t a, m;
		DATA d(arith<CPU>::get_cpu(), this);
		OP op(arith<CPU>::get_cpu(), this);

		a = arith<CPU>::get_cpu()->get_A();
		m = d.fetch(false);
		arith<CPU>::get_cpu()->set_A(op.calculate(a, m));
	}
};

template<typename CPU, typename DATA, typename OP>
class rmw_arith : public arith<CPU> {
public:
	using arith<CPU>::arith;

	virtual void execute() override {
		std::uint8_t a;
		OP op(arith<CPU>::get_cpu(), this);
		DATA d(arith<CPU>::get_cpu(), this);

		a = arith<CPU>::get_cpu()->get_latch();
		d.store(op.calculate(a));
	}
};

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
