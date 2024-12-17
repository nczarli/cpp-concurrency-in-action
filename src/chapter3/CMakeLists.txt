cmake_minimum_required(VERSION 3.15)
project(BasicThreadingExample)

# Set the C++ standard to C++11 or higher (required for threading support)
set(CMAKE_CXX_STANDARD 23)

# Add the source files to the project

# add_executable(app ../1_protecting_shared_data_using_mutex.cpp)
# add_executable(app ../2_demonstrating_race_conditions.cpp)
# add_executable(app ../3_avoiding_deadlock_using_lock.cpp)
# add_executable(app ../4_threadsafe_stack.cpp)
# add_executable(app ../5_threadsafe_queue.cpp)
add_executable(app ../6_threadsafe_log_writer.cpp)

# Link the project with any Conan dependencies
target_link_libraries(app ${CONAN_LIBS})
