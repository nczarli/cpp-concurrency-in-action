cmake_minimum_required(VERSION 3.15)
project(BasicThreadingExample)

# Set the C++ standard to C++11 or higher (required for threading support)
set(CMAKE_CXX_STANDARD 23)

# Add the source files to the project
# add_executable(app ../1_basic_thread_creation_and_joining.cpp)
# add_executable(app ../2_detaching_a_thread.cpp)
# add_executable(app ../3_passing_arguments_to_threads.cpp)
# add_executable(app ../4_thread_guard.cpp)
# add_executable(app ../5_scoped_thread.cpp)
# add_executable(app ../6_thread_identification.cpp)
add_executable(app ../7_parallel_accumulation.cpp)

# Link the project with any Conan dependencies
target_link_libraries(app ${CONAN_LIBS})
