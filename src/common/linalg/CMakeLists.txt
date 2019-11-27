file(GLOB SOURCES ./*.h ./*.cpp ../exceptions/*)

add_library(common SHARED ${SOURCES})

include_directories('${CMAKE_CURRENT_LIST_DIR}/../exceptions')

set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_LIST_DIR})