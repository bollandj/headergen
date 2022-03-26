set(TEST_HEADERGEN_TREE_EXECUTABLE_NAME test_headergen_tree)

add_executable(${TEST_HEADERGEN_TREE_EXECUTABLE_NAME} test_headergen_tree.c ../../src/headergen_tree.c)
target_include_directories(${TEST_HEADERGEN_TREE_EXECUTABLE_NAME} PRIVATE . ../../src)

target_compile_options(${TEST_HEADERGEN_TREE_EXECUTABLE_NAME} PRIVATE
        -Wall
)