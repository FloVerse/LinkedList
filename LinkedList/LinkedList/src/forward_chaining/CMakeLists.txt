set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

add_library(forward_chaining SHARED 
	./forward-chaining.c 
	./forward-chaining.h 
	./forward-chaining.inc
)

set_target_properties(forward_chaining PROPERTIES VERSION ${PROJECT_VERSION})

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/forward_chaining.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/forward_chaining.pc
	@ONLY
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/forward_chaining.pc		
	DESTINATION share/pkgconfig
	COMPONENT "PkgConfig"
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/ForwardChainingConfig.cmake.in	
	${CMAKE_CURRENT_BINARY_DIR}/ForwardChaining.cmake
	INSTALL_DESTINATION cmake
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/ForwardChaining.cmake
	DESTINATION cmake
)

install(
	TARGETS forward_chaining
	LIBRARY DESTINATION lib COMPONENT "Library"
	ARCHIVE DESTINATION lib COMPONENT "Library"
	RUNTIME DESTINATION bin COMPONENT "Runtime"
)

install(
	FILES forward-chaining.h
	DESTINATION include
	COMPONENT "Header"
)

add_executable(rules rules.c)
add_dependencies(rules forward_chaining)
target_link_libraries(rules forward_chaining)
