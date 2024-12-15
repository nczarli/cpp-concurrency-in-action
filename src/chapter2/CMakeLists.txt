cmake_minimum_required(VERSION 3.15)
project(BasicThreadingExample)

# Set the C++ standard to C++11 or higher (required for threading support)
set(CMAKE_CXX_STANDARD 23)

# Add the source files to the project
add_executable(basic_thread_example ../1_basic_thread_creation_and_joining.cpp)

# Link the project with any Conan dependencies
target_link_libraries(basic_thread_example ${CONAN_LIBS})
