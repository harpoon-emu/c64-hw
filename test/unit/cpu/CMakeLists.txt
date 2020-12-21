add_executable(
    t_cpu_runner
    mos_6510_flags.cc
)

target_link_libraries(
	t_cpu_runner
	gtest_main
	c64-hw
	)

add_test(
	NAME
	C64-HW/CPU
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/cpu/t_cpu_runner
	)

