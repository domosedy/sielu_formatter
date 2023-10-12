cmake_minimum_required(VERSION 3.25)
set(NAME domo-format)
project(${NAME})

set(CMAKE_CXX_STANDARD 23)

include_directories("include/")

set(FILES src/main.cpp src/file_parser.cpp)

##### PROJECT ######
add_executable(${NAME}
                ${FILES})
#####   END   ######