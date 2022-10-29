set(EXECUTABLE_NAME headergen)

add_executable(${EXECUTABLE_NAME} main.c lcrs_tree.c headergen_parser.c headergen_writer.c)
target_include_directories(${EXECUTABLE_NAME} PRIVATE .)

find_library(LIBYAML yaml)
target_link_libraries(${EXECUTABLE_NAME} "${LIBYAML}")

target_compile_options(${EXECUTABLE_NAME} PRIVATE
        -Wall
)