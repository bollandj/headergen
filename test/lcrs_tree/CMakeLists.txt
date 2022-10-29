set(TEST_LCRS_TREE_EXECUTABLE_NAME test_lcrs_tree)

add_executable(${TEST_LCRS_TREE_EXECUTABLE_NAME} test_lcrs_tree.c ../../src/lcrs_tree.c)
target_include_directories(${TEST_LCRS_TREE_EXECUTABLE_NAME} PRIVATE . ../../src)

target_compile_options(${TEST_LCRS_TREE_EXECUTABLE_NAME} PRIVATE
        -Wall
)