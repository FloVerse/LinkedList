find_program(DOXYGEN_EXECUTABLE doxygen)

find_program(SPHINX_EXECUTABLE sphinx-build)


if (SPHINX_EXECUTABLE AND DOXYGEN_EXECUTABLE)
	file(GLOB_RECURSE DOCUMENTED_FILES
	        "${CMAKE_SOURCE_DIR}/src/forward_chaining/*.h"
		"${CMAKE_SOURCE_DIR}/src/forward_chaining/*.inc")
		
	set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/src)       	 
	set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
	set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIRECTORY}/xml/index.xml)
	set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
	set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
	set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/html)
	set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)
	
	configure_file(${DOXYFILE_IN} ${DOXYFILE})
	file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY})
	add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}                                                                    
						COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE} 
						WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
						DEPENDS ${DOCUMENTED_FILES} ${DOXYFILE_IN} ${DOXYFILE} 
						COMMENT "Generating Doxygen XML" 
						VERBATIM)
						
	add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
						COMMAND ${SPHINX_EXECUTABLE} -b html 
						-Dbreathe_projects.BDP=${DOXYGEN_OUTPUT_DIRECTORY}/xml 
						${SPHINX_SOURCE} ${SPHINX_BUILD} 
						WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
						DEPENDS ${SPHINX_SOURCE}/conf.py ${CMAKE_CURRENT_SOURCE_DIR}/*.rst ${DOXYGEN_INDEX_FILE} 
						COMMENT "Generating Sphinx documentation")
	add_custom_target(docs DEPENDS ${DOXYGEN_INDEX_FILE} ${SPHINX_INDEX_FILE})
endif()
