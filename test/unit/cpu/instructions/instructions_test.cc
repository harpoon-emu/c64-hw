#include "instructions_test.hh"

#include "mocks/memory.hh"

namespace test {
namespace unit {
namespace cpu {
namespace instructions {

void instructions_test::SetUp() {
	_memory.reset(new mocks::memory());
	_mos_6510.set_memory(_memory);
}

} // namespace instructions
} // namespace cpu
} // namespace unit
} // namespace test
