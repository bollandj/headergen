set(TEST_HEADERGEN_WRITER_EXECUTABLE_NAME test_headergen_writer)

add_executable(${TEST_HEADERGEN_WRITER_EXECUTABLE_NAME} test_headergen_writer.c ../../src/headergen_writer.c)
target_include_directories(${TEST_HEADERGEN_WRITER_EXECUTABLE_NAME} PRIVATE . ../../src)

target_compile_options(${TEST_HEADERGEN_WRITER_EXECUTABLE_NAME} PRIVATE
        -Wall
)