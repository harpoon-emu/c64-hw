#ifndef CPU_INSTRUCTIONS_CPU_ACCESSOR_HH
#define CPU_INSTRUCTIONS_CPU_ACCESSOR_HH

#include "instruction_step_op.hh"

#include <cstdint>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, typename T>
class cpu_accessor : public instruction_step_op<CPU, T> {
public:
	using instruction_step_op<CPU, T>::instruction_step_op;

	T get() const {
		return {};
	};
	void set(T v) {}
};

#define _DEFINE_ACCESSOR(REG, T)                                 \
	template<typename CPU>                                       \
	class REG##_accessor : public cpu_accessor<CPU, T> {         \
	public:                                                      \
		using cpu_accessor<CPU, T>::cpu_accessor;                \
		T get() const {                                          \
			return cpu_accessor<CPU, T>::get_cpu()->get_##REG(); \
		}                                                        \
		void set(T v) {                                          \
			cpu_accessor<CPU, T>::get_cpu()->set_##REG(v);       \
		}                                                        \
	};

_DEFINE_ACCESSOR(A, std::uint8_t);
_DEFINE_ACCESSOR(X, std::uint8_t);
_DEFINE_ACCESSOR(Y, std::uint8_t);

_DEFINE_ACCESSOR(SP, std::uint8_t);

_DEFINE_ACCESSOR(PC, std::uint16_t);
_DEFINE_ACCESSOR(PCL, std::uint8_t);
_DEFINE_ACCESSOR(PCH, std::uint8_t);

_DEFINE_ACCESSOR(latch, std::uint8_t);

_DEFINE_ACCESSOR(P, std::uint8_t);
_DEFINE_ACCESSOR(flag_N, bool);
_DEFINE_ACCESSOR(flag_Z, bool);
_DEFINE_ACCESSOR(flag_C, bool);
_DEFINE_ACCESSOR(flag_I, bool);
_DEFINE_ACCESSOR(flag_D, bool);
_DEFINE_ACCESSOR(flag_V, bool);

} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif