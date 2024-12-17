#include <iostream>
#include <memory>
#include <stack>
#include <mutex>
#include <exception>

template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data;      // Internal stack to store data
    mutable std::mutex mtx;  // Mutex to protect the stack

public:
    threadsafe_stack() = default;

    // Disable copy constructor and copy assignment
    threadsafe_stack(const threadsafe_stack& other) = delete;
    threadsafe_stack& operator=(const threadsafe_stack& other) = delete;

    // Push an element onto the stack
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(mtx);
        data.push(std::move(new_value));
    }

    // Pop an element from the stack (returns void)
    void pop(T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) {
            throw std::runtime_error("Empty stack");
        }
        value = std::move(data.top());
        data.pop();
    }

    // Pop an element from the stack (returns smart pointer)
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) {
            throw std::runtime_error("Empty stack");
        }
        std::shared_ptr<T> result(std::make_shared<T>(data.top()));
        data.pop();
        return result;
    }

    // Check if the stack is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.empty();
    }

    // Get the size of the stack
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.size();
    }
};

int main(){
    threadsafe_stack<int> ts_stack;

    // Push elements
    ts_stack.push(10);
    ts_stack.push(20);
    ts_stack.push(30);

    // Get stack size
    std::cout << "Stack size: " << ts_stack.size() << std::endl;

    // Pop elements
    int value;
    ts_stack.pop(value);
    std::cout << "Popped value: " << value << std::endl;

    std::cout << "Stack size after pop: " << ts_stack.size() << std::endl;
    return 0;
}
