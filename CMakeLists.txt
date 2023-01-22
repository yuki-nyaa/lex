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

add_custom_command(OUTPUT Regex_Lexer.cpp Regex_Lexer.h
    COMMAND reflex ${PROJECT_SOURCE_DIR}/Regex_Lexer.l
    DEPENDS Regex_Lexer.l
    COMMENT "RE/flex-ing Regex_Lexer.l")
add_custom_target(Regex_Lexer
    DEPENDS Regex_Lexer.cpp Regex_Lexer.h)

add_custom_command(OUTPUT Regex_Parser.cpp Regex_Parser.h Regex_Parser.token.hpp
    COMMAND ypg -i ${PROJECT_SOURCE_DIR}/Regex_Parser.y -o Regex_Parser.cpp
    DEPENDS Regex_Parser.y
    COMMENT "YPG-ing Regex_Parser.y")
add_custom_target(Regex_Parser
    DEPENDS Regex_Parser.cpp Regex_Parser.h Regex_Parser.token.hpp)

add_executable(ylex main.cpp Regex_Lexer.cpp Regex_Parser.cpp)
target_link_libraries(ylex reflex fmt)