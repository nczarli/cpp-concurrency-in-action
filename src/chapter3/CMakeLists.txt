cmake_minimum_required(VERSION 3.15)
project(BasicThreadingExample)

# Set the C++ standard to C++11 or higher (required for threading support)
set(CMAKE_CXX_STANDARD 23)

# Add the source files to the project

# add_executable(app ../1_protecting_shared_data_using_mutex.cpp)
add_executable(app ../2_demonstrating_race_conditions.cpp)

# Link the project with any Conan dependencies
target_link_libraries(app ${CONAN_LIBS})
