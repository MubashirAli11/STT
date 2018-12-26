

file(GLOB SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )

add_library(stt ${SOURCES})
add_executable(demo main.cpp)
target_link_libraries(demo ${STTProject_LIBRARIES})
