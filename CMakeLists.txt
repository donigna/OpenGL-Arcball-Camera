cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

# Path to GLFW by manual installation
include_directories($ENV{CMAKE_ROOT}/usr/include)
link_directories($ENV{CMAKE_ROOT}/usr/lib)

# Add include path to GLAD
include_directories(${CMAKE_SOURCE_DIR}/external)
# Add internal include path
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(my_app 
    src/main.cpp
    src/glad.c  
)
target_link_libraries(my_app PRIVATE glfw SOIL GL m dl)
