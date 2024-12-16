#include <iostream>
#include <thread>
#include <vector>

void worker(int id){
    std::cout << "Thread " << id << " (ID : " << std::this_thread::get_id() << ") is working.\n";
}

int main(){
    const int num_threads = 5;
    std::vector<std::thread> threads;

    for (int i = 1; i <= num_threads; ++i){
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads){
        t.join();
    }

    std::cout << "All threads completed.\n";
    return 0;
}