cmake_minimum_required(VERSION 3.18.4)

project(Spark)

set(INCROOT include)
set(SRCROOT src)

set(ALL_SRC 
    ${SRCROOT}/Main.cpp

    ${INCROOT}/Server.hpp
    ${SRCROOT}/Server.cpp
    ${INCROOT}/Client.hpp
    ${SRCROOT}/Client.cpp
    ${INCROOT}/Game.hpp
    ${SRCROOT}/Game.cpp
)

add_executable(${PROJECT_NAME} ${ALL_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCROOT})

set(SFML_ROOT extlibs/SFML)
add_subdirectory(extlibs/Candle)
target_link_libraries(${PROJECT_NAME} PRIVATE Candle-s)

add_subdirectory(extlibs/SFML)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network)

add_custom_command(                                                                                                                                                       
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets2
)
