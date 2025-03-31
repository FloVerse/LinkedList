cmake_minimum_required(VERSION 3.0)

project(Forward_Chaining VERSION 1.0 DESCRIPTION " a forward chaining library")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(docs)

set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES ".*/\\\\..*;~$;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)
