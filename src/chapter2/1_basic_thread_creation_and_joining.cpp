#include <iostream>
#include <thread>

void print_message(const std::string& message) {
    for (int i = 0; i < 100; ++i) {
        std::cout << message << " - iteration " << i + 1 << "\n";
    }
}

int main() {
    std::thread thread1(print_message, "Thread 1 running");
    std::thread thread2(print_message, "Thread 2 running");

    thread1.join();
    thread2.join();

    std::cout << "Main thread finished.\n";
    return 0;
}
