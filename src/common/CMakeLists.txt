set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES exceptions/*.h linalg/*.h linalg/*.cpp linalg/inidices/*  video/*.h video/*.cpp)

add_library(common SHARED ${SOURCES} linalg/inidices/simple_index.cpp linalg/inidices/simple_index.h exceptions/index_overflow_exception.h)



set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_LIST_DIR})