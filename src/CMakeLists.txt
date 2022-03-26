set(EXECUTABLE_NAME headergen)

add_executable(${EXECUTABLE_NAME} main.c headergen.c headergen_tree.c headergen_writer.c)
target_include_directories(${EXECUTABLE_NAME} PRIVATE .)

find_library(LIBYAML yaml)
target_link_libraries(${EXECUTABLE_NAME} "${LIBYAML}")

target_compile_options(${EXECUTABLE_NAME} PRIVATE
        -Wall
)