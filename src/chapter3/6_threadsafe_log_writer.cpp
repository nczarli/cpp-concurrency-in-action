#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>

// Global mutex for synchronizing access to the log file
std::mutex log_mutex;

// Function to write messages to the log file
void write_to_log(std::ofstream& log_file, const std::string& thread_name, int messages) {
    for (int i = 1; i <= messages; ++i) {
        {
            // Lock the mutex before accessing the file
            std::lock_guard<std::mutex> lock(log_mutex);

            // Critical section: safely write to the file
            log_file << "Thread [" << thread_name << "] - Message " << i << std::endl;
            std::cout << "Thread [" << thread_name << "] wrote Message " << i << std::endl;
        }
        // Simulate some work between writes
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    // Open the shared log file
    std::ofstream log_file("shared_log.txt");
    if (!log_file.is_open()) {
        std::cerr << "Failed to open the log file!" << std::endl;
        return 1;
    }

    // Launch two threads writing to the log file
    std::thread t1(write_to_log, std::ref(log_file), "T1", 5);
    std::thread t2(write_to_log, std::ref(log_file), "T2", 5);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Close the log file
    log_file.close();
    std::cout << "Log file writing complete. Check 'shared_log.txt' for the output." << std::endl;

    return 0;
}
