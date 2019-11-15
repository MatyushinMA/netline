include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/local/include)

## build Graph
add_subdirectory(graph)

## build Learner
#add_subdirectory(learner)

## get utils sources
file(GLOB UTILS_SRC
    ${PROJECT_SOURCE_DIR}/utils/*.cpp
)

## build project
set(SOURCE_FILES main.cpp ${UTILS_SRC})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)
add_executable(netline ${SOURCE_FILES})

## link with modules
target_link_libraries(netline tensorflow Graph) # Learner)
set_target_properties(netline
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
