#include "harpoon/exception/harpoon_exception.hh"

using namespace harpoon::exception;

harpoon_exception::~harpoon_exception() {}

const char* harpoon_exception::what() const {
	return _what.c_str();
}
