include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

## build Graph
add_subdirectory(graph)

## get utils sources
file(GLOB UTILS_SRC
    ${PROJECT_SOURCE_DIR}/utils/*.cpp
)

## build project
set(SOURCE_FILES main.cpp ${UTILS_SRC})
add_executable(netline ${SOURCE_FILES})

## link with modules
target_link_libraries(netline Graph)
