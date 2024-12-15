#include <iostream>
#include <thread>
#include <vector>

class thread_guard{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t(t_){}
    ~thread_guard(){
        if (t.joinable()){
            t.join();
        }
    }

    // Disable copying and assignment
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};


void process_data(std::vector<int>& data){
    for (auto& num : data){
        num *= 2; // Double each element
    }
}


int main(){
    std::vector<int> data = {1, 2, 3, 4, 5};

    try{
        std::thread thread(process_data, std::ref(data));
        thread_guard guard(thread);

        // Simulate some exception
        throw std::runtime_error("An error occured!");
    } catch(const std::exception& e){
        std::cerr << e.what() << "\n";
    }

    for (const auto& num : data){
        std::cout << num << " ";
    }

    std::cout << "\n";
    return 0;
}


