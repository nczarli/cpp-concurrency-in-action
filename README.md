# cpp-concurrency-in-action
This repository contains my experiments while learning from the book "C++ Concurrency in Action" by Anthony Williams. The goal is to implement and explore the concepts of multithreading and concurrency in modern C++.


# Prerequisites

Before you begin, ensure that you have the following tools installed:

- C++ Compiler (e.g., g++)
- CMake (minimum version 3.10)
- Conan (for managing dependencies)


# Setting Up the Project

Follow these steps to build and run the example.

1. Clone the Repository

2. Install Dependencies with Conan

Run the following command to install any required dependencies using Conan:
```
conan install . --output-folder=build --build=missing
```
This will resolve any dependencies and create a conan_toolchain.cmake file in the build folder.

3. Configure the Project with CMake

Use CMake to configure the project with the Conan toolchain file:
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
This step configures the project and prepares it for the build process.

4. Build the Project

Now, compile the project using the following command:
```
cmake --build .
```
CMake will compile the project and generate the necessary binaries in the build directory.

5. Run the Program

License

This project is licensed under the MIT License - see the LICENSE file for details.
