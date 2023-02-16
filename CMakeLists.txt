cmake_minimum_required(VERSION 3.10)
project(yuki.lex VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-Wextra -Wno-missing-field-initializers -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified. Defaulted to 'Release'.")
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(YUKI_LEX_META_DBG TRUE)
    message("Build type: Debug")
else()
    set(YUKI_LEX_META_DBG FALSE)
    message("Build type: Release")
endif()

configure_file(cconfig.in cconfig)

include_directories(${PROJECT_SOURCE_DIR}/include /usr/local/include ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
link_directories(/usr/local/lib)

if(NOT YUKI_LEX_BUILD_WITH_PREGEN)
    set(CMAKE_CROSSCOMPILING TRUE)

    add_custom_target(build-time-make-directory ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/gen)

    add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/gen/Regex_Parser.cpp ${PROJECT_SOURCE_DIR}/gen/Regex_Parser.h ${PROJECT_SOURCE_DIR}/gen/Regex_Parser.token.hpp
        COMMAND ypg -i Regex_Parser.y -o gen/Regex_Parser.cpp -l gen/Regex_Parser.log
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        DEPENDS Regex_Parser.y build-time-make-directory
        COMMENT "ypg-ing Regex_Parser.y")
    add_custom_target(Regex_Parser
        DEPENDS ${PROJECT_SOURCE_DIR}/gen/Regex_Parser.cpp ${PROJECT_SOURCE_DIR}/gen/Regex_Parser.h ${PROJECT_SOURCE_DIR}/gen/Regex_Parser.token.hpp)

    add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/gen/Meta_Lexer.cpp ${PROJECT_SOURCE_DIR}/gen/Meta_Lexer.h
        COMMAND ylex -i Meta_Lexer.l -o gen/Meta_Lexer.cpp
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        DEPENDS Meta_Lexer.l build-time-make-directory
        COMMENT "ylex-ing Meta_Lexer.l")
    add_custom_target(Meta_Lexer
        DEPENDS ${PROJECT_SOURCE_DIR}/gen/Meta_Lexer.cpp ${PROJECT_SOURCE_DIR}/gen/Meta_Lexer.h)
endif()

add_executable(ylex main.cpp gen/Regex_Parser.cpp gen/Meta_Lexer.cpp write_fsm_code.cpp)
target_link_libraries(ylex fmt reflex)

install(DIRECTORY include/yuki TYPE INCLUDE)
install(TARGETS ylex RUNTIME)
