add_executable(
    t_cpu_instructions_runner
    instruction_step_op.cc
)

target_link_libraries(
	t_cpu_instructions_runner
	gmock_main
	c64-hw
	)

add_test(
	NAME
	C64-HW/CPU/Instructions
	COMMAND
		${CMAKE_BINARY_DIR}/test/unit/cpu/instructions/t_cpu_instructions_runner
	)

