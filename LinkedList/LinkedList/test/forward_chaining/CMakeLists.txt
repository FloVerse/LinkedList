# From cmake doc : The path to the top level of the source tree.
include_directories(${CMAKE_SOURCE_DIR}/src/forward_chaining)

find_package(Valgrind)

file(GLOB TEST_SRC
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/test-*.c"
)

foreach(TEST_FILE_NAME ${TEST_SRC})
    string(REPLACE ".c" "" TEST_NAME ${TEST_FILE_NAME})
    add_executable(${TEST_NAME} ${TEST_FILE_NAME})
    add_dependencies(${TEST_NAME} forward_chaining)

    target_link_libraries(${TEST_NAME} forward_chaining)
	
    valgrind_test(${TEST_NAME} ./${TEST_NAME})
endforeach(TEST_FILE_NAME ${TEST_SRC})

# Copying the files from the source to the build for the tests
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/example.fact.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/example.rule.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
