#ifndef HARPOON_EXCEPTION_HARDWARE_COMPONENT_EXCEPTION_HH
#define HARPOON_EXCEPTION_HARDWARE_COMPONENT_EXCEPTION_HH

#include "harpoon/harpoon.hh"
#include "harpoon/exception/harpoon_exception.hh"

namespace harpoon {
namespace exception {

class hardware_component_exception : public harpoon_exception {
public:

	hardware_component_exception(const std::string& component,
								 const std::string& what = {},
								 const std::string& file = {},
								 uint32_t line = {},
								 const std::string& function = {})
		: harpoon_exception(what, file, line, function), _component(component) {}

	virtual ~hardware_component_exception();

private:
	std::string _component{};
};

#define COMPONENT_EXCEPTION(EXCEPTION, ...)	\
	MAKE_HARPOON_EXCEPTION(EXCEPTION, this->get_name(), __VA_ARGS__);

}
}

#endif