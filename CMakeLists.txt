cmake_minimum_required(VERSION 3.18.4)

project(Spark)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(INCROOT include)
set(SRCROOT src)

set(ALL_SRC 
    ${SRCROOT}/Main.cpp
    ${INCROOT}/Game.hpp
    ${SRCROOT}/Game.cpp
    ${INCROOT}/Network/Network.hpp
    ${SRCROOT}/Network/Network.cpp
    ${INCROOT}/Network/TcpHandler.hpp
    ${SRCROOT}/Network/TcpHandler.cpp
    ${INCROOT}/Network/UdpHandler.hpp
    ${SRCROOT}/Network/UdpHandler.cpp
    
    ${INCROOT}/Utils/Config.hpp
    ${INCROOT}/Utils/Utils.hpp
    ${INCROOT}/Utils/Utils.inl
    ${SRCROOT}/Utils/Utils.cpp
    
)

add_executable(${PROJECT_NAME} ${ALL_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE  ${INCROOT} ${INCROOT}/Utils ${INCROOT}/Network)

set(SFML_ROOT extlibs/SFML)
add_subdirectory(extlibs/Candle)
target_link_libraries(${PROJECT_NAME} PRIVATE Candle-s)

add_subdirectory(extlibs/SFML)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_command(                                                                                                                                                       
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
