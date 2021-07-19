#ifndef CPU_INSTRUCTIONS_DATA_ACCESSOR_HH
#define CPU_INSTRUCTIONS_DATA_ACCESSOR_HH

#include "instruction_step_op.hh"

#include <cstdint>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {

template<typename CPU, typename T>
class data_accessor : public instruction_step_op<CPU, T> {
public:
	using instruction_step_op<CPU, T>::instruction_step_op;

	T fetch(bool update_flags) const {
		return {};
	}
	void store(T v) {}
};

template<typename CPU, typename T, typename REG>
class register_accessor : public data_accessor<CPU, T> {
public:
	using data_accessor<CPU, T>::data_accessor;

	T fetch(bool update_flags) const {
		REG reg(data_accessor<CPU, T>::get_cpu(), data_accessor<CPU, T>::get_instruction_step());
		T v = reg.get();
		if (update_flags) {
			data_accessor<CPU, T>::update_flags_NZ(v);
		}
		return v;
	}
};

template<typename CPU, typename T, T value>
class value_accessor : public data_accessor<CPU, T> {
public:
	using data_accessor<CPU, T>::data_accessor;

	T fetch(bool update_flags) const {
		if (update_flags) {
			data_accessor<CPU, T>::update_flags_NZ(value);
		}
		return value;
	}
};

template<typename CPU>
class program_code_accessor : public data_accessor<CPU, std::uint16_t> {
public:
	using data_accessor<CPU, std::uint16_t>::data_accessor;

	std::uint16_t fetch(bool update_flags) const {
		CPU *cpu = data_accessor<CPU, std::uint16_t>::get_cpu();

		cpu->internal_read_program_code();
		std::uint16_t v = cpu->get_internal_memory_access().w;
		if (update_flags) {
			data_accessor<CPU, std::uint16_t>::update_flags_NZ(v);
		}
		return v;
	}
};

template<typename CPU, typename T>
class immediate_accessor : public data_accessor<CPU, T> {
public:
	using data_accessor<CPU, T>::data_accessor;

	T fetch(bool update_flags) const {
		T v;
		data_accessor<CPU, T>::get_cpu()->get_program_code(v);
		if (update_flags) {
			data_accessor<CPU, T>::update_flags_NZ(v);
		}
		return v;
	}
};

template<typename CPU>
class memory_accessor : public data_accessor<CPU, std::uint8_t> {
public:
	using data_accessor<CPU, std::uint8_t>::data_accessor;

	std::uint8_t fetch(std::uint16_t address, std::uint8_t index, bool update_flags = true) const {
		std::uint8_t v;
		std::uint16_t a = address + index;
		data_accessor<CPU, std::uint8_t>::get_cpu()->get_memory()->get(a, v);
		if (update_flags) {
			data_accessor<CPU, std::uint8_t>::update_flags_NZ(v);
		}

		if ((a & 0xFF00) != (address & 0xFF00)) {
			data_accessor<CPU, std::uint8_t>::get_instruction_step()->add_delay(1);
		}

		return v;
	}

	void store(std::uint8_t v, std::uint16_t address, std::uint8_t index) {
		std::uint16_t a = address + index;
		data_accessor<CPU, std::uint8_t>::get_cpu()->get_memory()->set(a, v);
	}
};

template<typename CPU>
class zero_page_accessor : public memory_accessor<CPU> {
public:
	using memory_accessor<CPU>::memory_accessor;

	std::uint8_t fetch(bool update_flags, std::uint8_t index = 0) const {
		return memory_accessor<CPU>::fetch(
		    (memory_accessor<CPU>::get_cpu()->get_internal_memory_access().b.current + index)
		        & 0xFF,
		    0, update_flags);
	}

	void store(std::uint8_t v, std::uint8_t index = 0) {
		memory_accessor<CPU>::store(
		    v,
		    (memory_accessor<CPU>::get_cpu()->get_internal_memory_access().b.current + index)
		        & 0xFF,
		    0);
	}
};

template<typename CPU, typename REG>
class indexed_zero_page_accessor : public zero_page_accessor<CPU> {
public:
	using zero_page_accessor<CPU>::zero_page_accessor;

	std::uint8_t fetch(bool update_flags) const {
		REG r(zero_page_accessor<CPU>::get_cpu(), zero_page_accessor<CPU>::get_instruction_step());
		return zero_page_accessor<CPU>::fetch(update_flags, r.get());
	}

	void store(std::uint8_t v) {
		REG r(zero_page_accessor<CPU>::get_cpu(), zero_page_accessor<CPU>::get_instruction_step());
		zero_page_accessor<CPU>::store(v, r.get());
	}
};

template<typename CPU>
class absolute_accessor : public memory_accessor<CPU> {
public:
	using memory_accessor<CPU>::memory_accessor;

	std::uint8_t fetch(bool update_flags, std::uint8_t index = 0) const {
		return memory_accessor<CPU>::fetch(
		    memory_accessor<CPU>::get_cpu()->get_internal_memory_access().w, index, update_flags);
	}

	void store(std::uint8_t v, std::uint8_t index = 0) {
		memory_accessor<CPU>::store(
		    v, memory_accessor<CPU>::get_cpu()->get_internal_memory_access().w, index);
	}
};

template<typename CPU, typename REG>
class indexed_absolute_accessor : public absolute_accessor<CPU> {
public:
	using absolute_accessor<CPU>::absolute_accessor;

	std::uint8_t fetch(bool update_flags) const {
		REG r(absolute_accessor<CPU>::get_cpu(), absolute_accessor<CPU>::get_instruction_step());
		return absolute_accessor<CPU>::fetch(update_flags, r.get());
	}

	void store(std::uint8_t v) {
		REG r(absolute_accessor<CPU>::get_cpu(), absolute_accessor<CPU>::get_instruction_step());
		absolute_accessor<CPU>::store(v, r.get());
	}
};

template<typename CPU>
class indirect_accessor : public memory_accessor<CPU> {
public:
	using memory_accessor<CPU>::memory_accessor;

	std::uint8_t fetch(bool update_flags, std::uint8_t index = 0) const {
		return memory_accessor<CPU>::fetch(memory_accessor<CPU>::get_cpu()->get_indirect_pointer(),
		                                   index, update_flags);
	}

	void store(std::uint8_t v, std::uint8_t index = 0) {
		memory_accessor<CPU>::store(v, memory_accessor<CPU>::get_cpu()->get_indirect_pointer(),
		                            index);
	}
};

template<typename CPU, typename REG>
class indexed_indirect_accessor : public indirect_accessor<CPU> {
public:
	using indirect_accessor<CPU>::indirect_accessor;

	std::uint8_t fetch(bool update_flags = true) const {
		REG r(indirect_accessor<CPU>::get_cpu(), indirect_accessor<CPU>::get_instruction_step());
		return indirect_accessor<CPU>::fetch(update_flags, r.get());
	}

	void store(std::uint8_t v) {
		REG r(indirect_accessor<CPU>::get_cpu(), indirect_accessor<CPU>::get_instruction_step());
		indirect_accessor<CPU>::store(v, r.get());
	}
};


} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif