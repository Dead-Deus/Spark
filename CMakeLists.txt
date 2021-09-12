cmake_minimum_required(VERSION 3.18.4)

project(Spark)

set(INC include)
set(SRC src)

set(ALL_SRC 
    ${SRC}/Main.cpp
)

add_executable(${PROJECT_NAME} ${ALL_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCROOT})

find_package(SFML COMPONENTS system window graphics network REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network)

add_subdirectory(extlibs/Candle)
target_link_libraries(${PROJECT_NAME} PRIVATE Candle-s)

add_custom_command(                                                                                                                                                       
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_SOURCE_DIR}/build/assets
)
