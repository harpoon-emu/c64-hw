cmake_minimum_required(VERSION 3.9)

set(C64-hw_MAJOR_VERSION 0)
set(C64-hw_MINOR_VERSION 1)
set(C64-hw_PATCH_VERSION 0)
set(C64-hw_VERSION
  ${C64-hw_MAJOR_VERSION}.${C64-hw_MINOR_VERSION}.${C64-hw_PATCH_VERSION})

project(C64-hw LANGUAGES CXX C VERSION ${C64-hw_VERSION})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

find_package(Harpoon REQUIRED)

add_library(c64-hw SHARED
	src/memory/flat_memory.cc
	src/memory/memory.cc
	src/memory/compound_memory.cc
	src/cpu/mos_6510.cc
	src/cpu/instructions/pha.cc
	src/cpu/instructions/ror.cc
	src/cpu/instructions/bne.cc
	src/cpu/instructions/sed.cc
	src/cpu/instructions/sei.cc
	src/cpu/instructions/cld.cc
	src/cpu/instructions/rts.cc
	src/cpu/instructions/dex.cc
	src/cpu/instructions/brk.cc
	src/cpu/instructions/lda.cc
	src/cpu/instructions/dey.cc
	src/cpu/instructions/cli.cc
	src/cpu/instructions/tya.cc
	src/cpu/instructions/stx.cc
	src/cpu/instructions/plp.cc
	src/cpu/instructions/sec.cc
	src/cpu/instructions/ora.cc
	src/cpu/instructions/nop.cc
	src/cpu/instructions/bmi.cc
	src/cpu/instructions/clv.cc
	src/cpu/instructions/rti.cc
	src/cpu/instructions/txs.cc
	src/cpu/instructions/adc.cc
	src/cpu/instructions/txa.cc
	src/cpu/instructions/bvc.cc
	src/cpu/instructions/cpx.cc
	src/cpu/instructions/and.cc
	src/cpu/instructions/tax.cc
	src/cpu/instructions/cpy.cc
	src/cpu/instructions/ldx.cc
	src/cpu/instructions/bcs.cc
	src/cpu/instructions/ldy.cc
	src/cpu/instructions/sty.cc
	src/cpu/instructions/pla.cc
	src/cpu/instructions/bcc.cc
	src/cpu/instructions/eor.cc
	src/cpu/instructions/jmp.cc
	src/cpu/instructions/php.cc
	src/cpu/instructions/rol.cc
	src/cpu/instructions/jsr.cc
	src/cpu/instructions/bit.cc
	src/cpu/instructions/bvs.cc
	src/cpu/instructions/cmp.cc
	src/cpu/instructions/iny.cc
	src/cpu/instructions/tay.cc
	src/cpu/instructions/beq.cc
	src/cpu/instructions/inx.cc
	src/cpu/instructions/instruction_step.cc
	src/cpu/instructions/tsx.cc
	src/cpu/instructions/sbc.cc
	src/cpu/instructions/bpl.cc
	src/cpu/instructions/lsr.cc
	src/cpu/instructions/inc.cc
	src/cpu/instructions/disassembler.cc
	src/cpu/instructions/clc.cc
	src/cpu/instructions/sta.cc
	src/cpu/instructions/asl.cc
	src/cpu/instructions/arith_instruction.cc
	src/cpu/instructions/dec.cc
	src/c64.cc
)

set_target_properties(c64-hw PROPERTIES VERSION ${C64-hw_VERSION})
set_target_properties(c64-hw PROPERTIES SOVERSION ${C64-hw_MAJOR_VERSION})
set_target_properties(c64-hw PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_compile_features(c64-hw
	PUBLIC
		cxx_constexpr
		cxx_auto_type
		cxx_variadic_templates
	PRIVATE
		cxx_lambdas
		cxx_range_for
)

target_include_directories(c64-hw
	PUBLIC
		$<BUILD_INTERFACE:${C64-hw_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(c64-hw Harpoon::harpoon)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(c64-hw PUBLIC
		-O0
		-g
		-fprofile-arcs
		--coverage
		)
	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
		target_link_options(c64-hw PUBLIC --coverage)
	else()
		target_link_libraries(c64-hw PUBLIC --coverage)
	endif()
endif()

install(TARGETS c64-hw EXPORT Harpoon_C64-hwTargets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT Harpoon_C64-hwTargets
	NAMESPACE Harpoon::
	FILE Harpoon_C64-hwTargets.cmake
	DESTINATION ${CMAKE_INSTALL_DATADIR}/Harpoon/cmake
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/Harpoon_C64-hwConfigVersion.cmake
	VERSION ${C64-hw_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES 
			${CMAKE_CURRENT_BINARY_DIR}/Harpoon_C64-hwConfigVersion.cmake
			Harpoon_C64-hwConfig.cmake
		DESTINATION ${CMAKE_INSTALL_DATADIR}/Harpoon/cmake
)

export(TARGETS c64-hw NAMESPACE Harpoon:: FILE Harpoon_C64-hwConfig.cmake)

# GTEST

enable_testing()

if (BUILD_TESTING)
	include(cmake/googletest.cmake)
	fetch_googletest(
		${PROJECT_SOURCE_DIR}/cmake
		${PROJECT_BINARY_DIR}/googletest
		)
	add_subdirectory(test)
endif()
