#include "harpoon/c64-hw/memory/memory.hh"

#include <harpoon/memory/chunked_random_access_memory.hh>
#include <harpoon/memory/chunked_read_only_memory.hh>
#include <harpoon/memory/linear_random_access_memory.hh>
#include <harpoon/memory/linear_read_only_memory.hh>
#include <harpoon/memory/serializer/binary_file.hh>

namespace c64 {
namespace hw {
namespace memory {

memory::~memory() {}

} // namespace memory
} // namespace hw
} // namespace c64
