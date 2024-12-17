#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <exception>
#include <chrono>

struct empty_queue : std::exception {
    const char* what() const throw() { return "Queue is empty"; }
};

template <typename T>
class threadsafe_queue {
private:
    std::queue<T> data_queue;
    mutable std::mutex mtx;

public:
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(mtx);
        data_queue.push(new_value);
    }

    T pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (data_queue.empty()) throw empty_queue();
        T value = data_queue.front();
        data_queue.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data_queue.empty();
    }
};

void producer(threadsafe_queue<int>& q, int start, int end) {
    for (int i = start; i <= end; ++i) {
        q.push(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate work
    }
}

void consumer(threadsafe_queue<int>& q, int id, int count) {
    for (int i = 0; i < count; ++i) {
        try {
            int value = q.pop();
            std::cout << "Consumer " << id << " consumed: " << value << std::endl;
        } catch (const empty_queue& e) {
            std::cout << "Consumer " << id << ": " << e.what() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
}

int main() {
    threadsafe_queue<int> q;

    // Launch producers
    std::thread producer1(producer, std::ref(q), 1, 10);
    std::thread producer2(producer, std::ref(q), 11, 20);

    // Launch consumers
    std::thread consumer1(consumer, std::ref(q), 1, 10);
    std::thread consumer2(consumer, std::ref(q), 2, 10);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    std::cout << "Final Queue empty: " << (q.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
