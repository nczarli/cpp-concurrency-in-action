#include <iostream>
#include <thread>
#include <chrono>

void print_message1(const std::string& message) {
    for (int i = 0; i < 5; ++i) {
        std::cout << message << " - iteration " << i + 1 << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void print_message2(const std::string& message) {
    for (int i = 0; i < 20; ++i) {
        std::cout << message << " - iteration " << i + 1 << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread thread1(print_message1, "Thread 1 running");
    std::thread thread2(print_message2, "Thread 2 running");

    thread2.detach(); // Runs in the background
    thread1.join();   // Main thread waits for this

    std::cout << "Main thread finished. Detached thread may still be running.\n";
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Ensure detached thread finishes
    return 0;
}

